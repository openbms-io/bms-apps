#!/bin/bash
#
# Build FMU from OpenModelica-generated source code for the current host platform
# Usage: ./build-fmu.sh <fmu-source-dir> [output-dir]
#
# Example:
#   ./build-fmu.sh ../reheat/Controllerc79b/824.fmutmp
#   ./build-fmu.sh ../reheat/Controllerc79b/824.fmutmp ../output
#

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

print_status() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Check arguments
if [ $# -lt 1 ]; then
    echo "Usage: $0 <fmu-source-dir> [output-dir]"
    echo ""
    echo "Arguments:"
    echo "  fmu-source-dir  Path to extracted FMU directory containing sources/ and modelDescription.xml"
    echo "  output-dir      Optional output directory for the compiled FMU (default: same as source)"
    echo ""
    echo "Example:"
    echo "  $0 ../reheat/Controllerc79b/824.fmutmp"
    exit 1
fi

FMU_SOURCE_DIR="$1"
OUTPUT_DIR="${2:-$(dirname "$FMU_SOURCE_DIR")}"

# Validate source directory first (before converting to absolute path)
if [ ! -d "$FMU_SOURCE_DIR" ]; then
    print_error "Source directory does not exist: $FMU_SOURCE_DIR"
    exit 1
fi

if [ ! -f "$FMU_SOURCE_DIR/modelDescription.xml" ]; then
    print_error "modelDescription.xml not found in $FMU_SOURCE_DIR"
    exit 1
fi

if [ ! -d "$FMU_SOURCE_DIR/sources" ]; then
    print_error "sources/ directory not found in $FMU_SOURCE_DIR"
    exit 1
fi

if [ ! -f "$FMU_SOURCE_DIR/sources/CMakeLists.txt" ]; then
    print_error "CMakeLists.txt not found in $FMU_SOURCE_DIR/sources/"
    exit 1
fi

# Convert to absolute paths now that validation is done
FMU_SOURCE_DIR="$(cd "$FMU_SOURCE_DIR" && pwd)"
mkdir -p "$OUTPUT_DIR"
OUTPUT_DIR="$(cd "$OUTPUT_DIR" && pwd)"

# Extract FMU name from CMakeLists.txt
FMU_NAME=$(grep "set(FMU_NAME " "$FMU_SOURCE_DIR/sources/CMakeLists.txt" | sed 's/.*set(FMU_NAME \([^)]*\)).*/\1/')
if [ -z "$FMU_NAME" ]; then
    print_error "Could not extract FMU_NAME from CMakeLists.txt"
    exit 1
fi

print_status "Building FMU: $FMU_NAME"
print_status "Source directory: $FMU_SOURCE_DIR"
print_status "Output directory: $OUTPUT_DIR"

# Check for required tools
if ! command -v cmake &> /dev/null; then
    print_error "cmake is required but not installed. Install with: brew install cmake"
    exit 1
fi

if ! command -v make &> /dev/null; then
    print_error "make is required but not installed. Install Xcode Command Line Tools: xcode-select --install"
    exit 1
fi

# Detect platform
PLATFORM=$(uname -s)
ARCH=$(uname -m)

case "$PLATFORM" in
    Darwin)
        if [ "$ARCH" = "arm64" ]; then
            FMU_PLATFORM="darwin64"  # FMI standard uses darwin64 for both Intel and ARM
        else
            FMU_PLATFORM="darwin64"
        fi
        LIBRARY_EXT="dylib"
        ;;
    Linux)
        if [ "$ARCH" = "x86_64" ]; then
            FMU_PLATFORM="linux64"
        else
            FMU_PLATFORM="linux32"
        fi
        LIBRARY_EXT="so"
        ;;
    MINGW*|MSYS*|CYGWIN*)
        if [ "$ARCH" = "x86_64" ]; then
            FMU_PLATFORM="win64"
        else
            FMU_PLATFORM="win32"
        fi
        LIBRARY_EXT="dll"
        ;;
    *)
        print_error "Unsupported platform: $PLATFORM"
        exit 1
        ;;
esac

print_status "Detected platform: $FMU_PLATFORM ($PLATFORM $ARCH)"

# Patch CMakeLists.txt for newer Apple Clang compatibility
# The original OpenModelica CMakeLists.txt uses linker flags that aren't compatible
# with newer Apple linkers (ld-prime/ld64.lld)
CMAKE_FILE="$FMU_SOURCE_DIR/sources/CMakeLists.txt"
if [ "$PLATFORM" = "Darwin" ]; then
    print_status "Patching CMakeLists.txt for macOS compatibility..."

    # Backup original
    cp "$CMAKE_FILE" "$CMAKE_FILE.bak"

    # Fix the AppleClang linker options - the new linker doesn't support the SHELL: syntax with comma-separated args
    # Change: target_link_options(... "LINKER:SHELL:-undefined,error")
    # To: Remove entirely (or use -Wl,-undefined,error which also may not work)
    # Safest: just remove the problematic linker options for macOS
    sed -i.tmp 's/target_link_options.*AppleClang.*LINKER:SHELL:-undefined,error.*/# Removed for macOS compatibility/' "$CMAKE_FILE"

    # Also handle if it's on multiple lines - just comment out the whole block
    sed -i.tmp '/if(CMAKE_C_COMPILER_ID STREQUAL "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "AppleClang")/,/endif()/s/target_link_options/#target_link_options/' "$CMAKE_FILE"

    rm -f "$CMAKE_FILE.tmp"
fi

# Create build directory
BUILD_DIR="$FMU_SOURCE_DIR/sources/build"
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"

print_status "Configuring CMake..."
cd "$BUILD_DIR"

# Configure with CMake
cmake .. \
    -DRUNTIME_DEPENDENCIES_LEVEL=none \
    -DBUILD_SHARED_LIBS=ON \
    2>&1 | while read line; do echo "  $line"; done

print_status "Building..."
make -j$(sysctl -n hw.ncpu 2>/dev/null || nproc 2>/dev/null || echo 4) \
    2>&1 | while read line; do echo "  $line"; done

print_status "Installing..."
make install \
    2>&1 | while read line; do echo "  $line"; done

# Restore original CMakeLists.txt
if [ -f "$CMAKE_FILE.bak" ]; then
    mv "$CMAKE_FILE.bak" "$CMAKE_FILE"
fi

# Verify the library was created
BINARY_DIR="$FMU_SOURCE_DIR/binaries/$FMU_PLATFORM"
if [ ! -f "$BINARY_DIR/$FMU_NAME.$LIBRARY_EXT" ]; then
    print_error "Build failed: $BINARY_DIR/$FMU_NAME.$LIBRARY_EXT not found"
    exit 1
fi

print_status "Library created: $BINARY_DIR/$FMU_NAME.$LIBRARY_EXT"

# Create the FMU zip file
print_status "Creating FMU package..."
cd "$FMU_SOURCE_DIR"

# Create output directory if needed
mkdir -p "$OUTPUT_DIR"

# Create FMU (zip file)
FMU_FILE="$OUTPUT_DIR/$FMU_NAME.fmu"
rm -f "$FMU_FILE"

# Zip the required contents
zip -r "$FMU_FILE" \
    binaries/ \
    resources/ \
    sources/ \
    modelDescription.xml \
    -x "sources/build/*" \
    2>&1 | while read line; do echo "  $line"; done

# Add documentation if it exists
if [ -d "documentation" ]; then
    zip -r "$FMU_FILE" documentation/ \
        2>&1 | while read line; do echo "  $line"; done
fi

print_status "FMU created successfully: $FMU_FILE"

# Show FMU contents summary
echo ""
print_status "FMU contents:"
unzip -l "$FMU_FILE" | grep "binaries/" | head -5

echo ""
print_status "Build complete!"
echo ""
echo "To use this FMU in Python with FMPy:"
echo "  pip install fmpy"
echo "  python -c \"import fmpy; fmpy.dump('$FMU_FILE')\""
