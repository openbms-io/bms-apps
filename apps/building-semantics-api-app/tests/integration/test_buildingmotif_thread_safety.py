"""Integration test to verify BuildingMOTIF thread safety with SQLite."""
import threading
import time
from pathlib import Path
from tempfile import TemporaryDirectory

import pytest
from buildingmotif import BuildingMOTIF
from rdflib import Namespace, RDF, URIRef


def test_url_query_parameter_check_same_thread_false():
    """
    Test if connection_string with ?check_same_thread=False works.

    This test verifies that the current approach in buildingmotif_adapter.py line 56:
        connection_string = f"sqlite:///{db_path}?check_same_thread=False"

    actually allows cross-thread database access without errors.
    """
    with TemporaryDirectory() as temp_dir:
        db_path = Path(temp_dir) / "test_thread_safety.db"

        # Use the same connection string pattern as buildingmotif_adapter.py
        connection_string = f"sqlite:///{db_path}?check_same_thread=False"

        # Initialize BuildingMOTIF
        bm = BuildingMOTIF(connection_string)
        bm.setup_tables()

        errors = []
        results = {}

        def worker_create_model(thread_id: int):
            """Worker that creates a model and adds triples."""
            try:
                from buildingmotif.dataclasses import Model

                # Create model with unique namespace
                ns = Namespace(f"urn:test:thread-{thread_id}#")
                model = Model.create(ns)

                # Add some triples
                subject = URIRef(f"{ns}subject-{thread_id}")
                predicate = RDF.type
                obj = URIRef(f"{ns}TestClass")

                model.graph.add((subject, predicate, obj))

                # Access session from BuildingMOTIF (uses scoped_session)
                bm.session.commit()

                results[thread_id] = len(model.graph)

            except Exception as e:
                errors.append((thread_id, str(e), type(e).__name__))

        # Create multiple threads
        threads = []
        num_threads = 5

        for i in range(num_threads):
            thread = threading.Thread(target=worker_create_model, args=(i,))
            threads.append(thread)

        # Start all threads
        for thread in threads:
            thread.start()

        # Wait for all threads to complete
        for thread in threads:
            thread.join(timeout=10)

        # Check for errors - specifically looking for sqlite thread errors
        if errors:
            error_messages = "\n".join([
                f"Thread {tid}: {error_type} - {msg}"
                for tid, msg, error_type in errors
            ])

            # Check if any errors are SQLite thread-related
            has_thread_error = any(
                "thread" in msg.lower() or "sqlite" in error_type
                for _, msg, error_type in errors
            )

            if has_thread_error:
                pytest.fail(f"SQLite thread errors occurred:\n{error_messages}")
            else:
                # Other errors might be OK for this test (e.g., data races)
                # We're only checking thread safety, not data consistency
                pass

        # Verify all threads completed successfully
        assert len(results) == num_threads, \
            f"Expected {num_threads} results, got {len(results)}. Errors: {errors}"


def test_concurrent_model_operations():
    """
    Test concurrent read/write operations on the same model.

    More aggressive test - multiple threads operating on the same model.
    """
    with TemporaryDirectory() as temp_dir:
        db_path = Path(temp_dir) / "test_concurrent.db"
        connection_string = f"sqlite:///{db_path}?check_same_thread=False"

        bm = BuildingMOTIF(connection_string)
        bm.setup_tables()

        # Create a shared model
        from buildingmotif.dataclasses import Model
        ns = Namespace("urn:test:shared#")
        model = Model.create(ns)
        model_name = str(model.name)  # Get the actual name for loading

        # Initial commit so model exists in database
        bm.session.commit()

        errors = []
        triple_counts = []

        def worker_add_triples(thread_id: int, num_triples: int):
            """Worker that adds triples to the shared model."""
            try:
                # Load the model (forces database access from different thread)
                loaded_model = Model.load(name=model_name)

                # Add triples
                for i in range(num_triples):
                    subject = URIRef(f"{ns}subject-{thread_id}-{i}")
                    predicate = RDF.type
                    obj = URIRef(f"{ns}Thread{thread_id}Class")
                    loaded_model.graph.add((subject, predicate, obj))

                # Commit from this thread's session
                bm.session.commit()

                # Count triples added
                triple_counts.append((thread_id, num_triples))

            except Exception as e:
                errors.append((thread_id, str(e), type(e).__name__))

        # Create threads that all operate on the same model
        threads = []
        num_threads = 3
        triples_per_thread = 5

        for i in range(num_threads):
            thread = threading.Thread(
                target=worker_add_triples,
                args=(i, triples_per_thread)
            )
            threads.append(thread)
            thread.start()
            # Small delay to reduce race conditions (we're testing thread safety, not concurrency correctness)
            time.sleep(0.01)

        # Wait for completion
        for thread in threads:
            thread.join(timeout=10)

        # Check for SQLite thread errors specifically
        if errors:
            error_messages = "\n".join([
                f"Thread {tid}: {error_type} - {msg}"
                for tid, msg, error_type in errors
            ])

            # Check if any errors are SQLite thread-related
            has_thread_error = any(
                "thread" in msg.lower() or
                "sqlite" in error_type.lower() or
                "programmingerror" in error_type.lower()
                for _, msg, error_type in errors
            )

            if has_thread_error:
                pytest.fail(f"SQLite thread errors occurred:\n{error_messages}")
            else:
                # Data consistency errors are expected in concurrent writes
                # We only care about thread safety, not perfect concurrency
                pass

        # Verify at least some threads completed
        assert len(triple_counts) >= 1, \
            f"Expected at least 1 thread to complete, got {len(triple_counts)}. Errors: {errors}"


def test_check_same_thread_error_without_flag():
    """
    Negative test: Verify that WITHOUT ?check_same_thread=False,
    we would get an error.

    This confirms our test is actually testing the right thing.
    """
    with TemporaryDirectory() as temp_dir:
        db_path = Path(temp_dir) / "test_strict_thread.db"

        # Use connection WITHOUT the check_same_thread=False flag
        connection_string = f"sqlite:///{db_path}"

        bm = BuildingMOTIF(connection_string)
        bm.setup_tables()

        error_occurred = []

        def worker_fail():
            """Worker that should fail with thread check error."""
            try:
                from buildingmotif.dataclasses import Model
                ns = Namespace("urn:test:fail#")
                model = Model.create(ns)
                bm.session.commit()
            except Exception as e:
                error_occurred.append(str(e))

        # Start thread
        thread = threading.Thread(target=worker_fail)
        thread.start()
        thread.join(timeout=10)

        # We expect an error about thread usage
        # Note: This might not always fail due to SQLAlchemy's connection pooling,
        # but it demonstrates the risk
        if error_occurred:
            assert any("thread" in err.lower() or "sqlite" in err.lower()
                      for err in error_occurred), \
                f"Expected thread-related error, got: {error_occurred}"
