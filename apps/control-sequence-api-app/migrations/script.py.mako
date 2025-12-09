<%doc>
Mako Template for Alembic Migration Files

This .mako template is used by Alembic to generate new migration Python files.
When you run: alembic revision --autogenerate -m "description"
Alembic fills in the ${...} variables to create a migration file.

Template Variables:
- ${message} → Your migration description
- ${up_revision} → Unique revision ID (auto-generated hash)
- ${down_revision} → Previous revision to chain migrations
- ${upgrades} → Auto-detected schema changes (CREATE TABLE, ADD COLUMN, etc.)
- ${downgrades} → Reverse operations (DROP TABLE, DROP COLUMN, etc.)
</%doc>
"""${message}

Revision ID: ${up_revision}
Revises: ${down_revision | comma,n}
Create Date: ${create_date}

"""
from typing import Sequence, Union

from alembic import op
import sqlalchemy as sa
${imports if imports else ""}

# revision identifiers, used by Alembic.
revision: str = ${repr(up_revision)}
down_revision: Union[str, Sequence[str], None] = ${repr(down_revision)}
branch_labels: Union[str, Sequence[str], None] = ${repr(branch_labels)}
depends_on: Union[str, Sequence[str], None] = ${repr(depends_on)}


def upgrade() -> None:
    """Upgrade schema."""
    ${upgrades if upgrades else "pass"}


def downgrade() -> None:
    """Downgrade schema."""
    ${downgrades if downgrades else "pass"}
