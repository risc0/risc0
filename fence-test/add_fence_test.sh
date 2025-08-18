#!/bin/bash
# Script to add fence instruction test to risc0 test suite
# This script is idempotent and can be run multiple times safely
#
# Prerequisites: fence.S and riscv-tests.ld must exist in the same directory as this script

set -euo pipefail

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Get the directory where this script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# BASE_DIR is the risc0 directory (parent of fence-test)
BASE_DIR="$(dirname "${SCRIPT_DIR}")"

# Configuration
TOOLCHAIN_VERSION="2022.03.25"
# Note: GitHub release downloads can be very slow. Consider downloading manually if needed.
# Alternative: wget https://github.com/risc0/toolchain/releases/download/2022.03.25/riscv32im-linux-x86_64.tar.xz
TOOLCHAIN_URL="https://github.com/risc0/toolchain/releases/download/${TOOLCHAIN_VERSION}/riscv32im-linux-x86_64.tar.xz"
TOOLCHAIN_DIR="riscv32im-linux-x86_64"
TEST_ARCHIVE="${BASE_DIR}/risc0/circuit/rv32im/src/prove/testdata/riscv-tests.tgz"
TEST_FILE="${BASE_DIR}/risc0/circuit/rv32im/src/prove/tests.rs"
FENCE_SOURCE="${SCRIPT_DIR}/fence.S"
FENCE_LINKER="${SCRIPT_DIR}/riscv-tests.ld"

# Print colored message
log() {
    echo -e "${GREEN}[+]${NC} $1"
}

error() {
    echo -e "${RED}[!]${NC} $1" >&2
}

warn() {
    echo -e "${YELLOW}[*]${NC} $1"
}

# Check prerequisites
check_prerequisites() {
    if [ ! -f "${FENCE_SOURCE}" ]; then
        error "fence.S not found at ${FENCE_SOURCE}"
        error "Please ensure fence.S exists in the same directory as this script"
        exit 1
    fi
    
    if [ ! -f "${FENCE_LINKER}" ]; then
        error "riscv-tests.ld not found at ${FENCE_LINKER}"
        error "Please ensure riscv-tests.ld exists in the same directory as this script"
        exit 1
    fi
    
    log "Prerequisites found"
}

# Create temporary working directory
setup_temp_dir() {
    TEMP_DIR=$(mktemp -d)
    log "Created temporary directory: ${TEMP_DIR}"
    
    # Ensure cleanup on exit
    trap cleanup EXIT
    
    cd "${TEMP_DIR}"
}

# Clean up temporary directory
cleanup() {
    if [ -n "${TEMP_DIR:-}" ] && [ -d "${TEMP_DIR}" ]; then
        log "Cleaning up temporary directory"
        rm -rf "${TEMP_DIR}"
    fi
}

# Download and extract toolchain if needed
setup_toolchain() {
    # Check if toolchain already exists in repo directory
    local toolchain_dir="${BASE_DIR}/riscv-tests-toolchain"
    
    # Check if the toolchain binaries actually exist
    if [ -d "${toolchain_dir}/${TOOLCHAIN_DIR}/bin" ] && [ -f "${toolchain_dir}/${TOOLCHAIN_DIR}/bin/riscv32-unknown-elf-gcc" ]; then
        warn "Toolchain already exists at ${toolchain_dir}, using existing installation"
        TOOLCHAIN_PATH="${toolchain_dir}/${TOOLCHAIN_DIR}"
        return
    fi
    
    # Remove incomplete toolchain if it exists
    if [ -d "${toolchain_dir}/${TOOLCHAIN_DIR}" ]; then
        warn "Incomplete toolchain found, removing and re-downloading"
        rm -rf "${toolchain_dir}/${TOOLCHAIN_DIR}"
    fi
    
    log "Downloading risc0 toolchain ${TOOLCHAIN_VERSION}"
    mkdir -p "${toolchain_dir}"
    cd "${toolchain_dir}"
    
    local archive_name="$(basename ${TOOLCHAIN_URL})"
    if [ ! -f "${archive_name}" ] || [ ! -s "${archive_name}" ]; then
        log "Downloading from ${TOOLCHAIN_URL}"
        log "This is a 28MB file - download may take a moment depending on connection speed"
        
        # Try curl first as it's often faster
        if command -v curl &> /dev/null; then
            curl -L --progress-bar -o "${archive_name}" "${TOOLCHAIN_URL}" || {
                error "Download failed with curl, trying wget"
                rm -f "${archive_name}"
                wget --progress=bar:force --show-progress -O "${archive_name}" "${TOOLCHAIN_URL}"
            }
        else
            wget --progress=bar:force --show-progress -O "${archive_name}" "${TOOLCHAIN_URL}"
        fi
        
        # Verify file size (should be about 28MB)
        local file_size=$(stat -c%s "${archive_name}" 2>/dev/null || stat -f%z "${archive_name}" 2>/dev/null)
        if [ "${file_size}" -lt 1000000 ]; then
            error "Downloaded file is too small (${file_size} bytes), likely corrupted"
            rm -f "${archive_name}"
            exit 1
        fi
    else
        log "Using cached toolchain archive"
    fi
    
    log "Extracting toolchain (this may take a moment)..."
    tar -xf "$(basename ${TOOLCHAIN_URL})"
    
    # Verify extraction was successful
    if [ ! -f "${toolchain_dir}/${TOOLCHAIN_DIR}/bin/riscv32-unknown-elf-gcc" ]; then
        error "Toolchain extraction failed - gcc not found"
        error "Please remove ${toolchain_dir} and try again"
        exit 1
    fi
    
    TOOLCHAIN_PATH="${toolchain_dir}/${TOOLCHAIN_DIR}"
    log "Toolchain ready at ${TOOLCHAIN_PATH}"
    cd "${TEMP_DIR}"
}

# Compile fence test
compile_fence_test() {
    log "Compiling fence test"
    
    # Copy source files to temp directory
    cp "${FENCE_SOURCE}" fence.S
    cp "${FENCE_LINKER}" riscv-tests.ld
    
    # Check if we have the toolchain
    local gcc_cmd=""
    if [ -n "${TOOLCHAIN_PATH:-}" ] && [ -f "${TOOLCHAIN_PATH}/bin/riscv32-unknown-elf-gcc" ]; then
        export PATH="${TOOLCHAIN_PATH}/bin:${PATH}"
        gcc_cmd="riscv32-unknown-elf-gcc"
    elif command -v riscv32-unknown-elf-gcc &> /dev/null; then
        gcc_cmd="riscv32-unknown-elf-gcc"
        log "Using system riscv32-unknown-elf-gcc"
    elif command -v riscv64-unknown-elf-gcc &> /dev/null; then
        gcc_cmd="riscv64-unknown-elf-gcc"
        log "Using system riscv64-unknown-elf-gcc with rv32im target"
    else
        error "No RISC-V toolchain found"
        error "Please install riscv-gnu-toolchain or wait for download to complete"
        return 1
    fi
    
    ${gcc_cmd} \
        -march=rv32im \
        -mabi=ilp32 \
        -static \
        -mcmodel=medany \
        -nostdlib \
        -nostartfiles \
        -T riscv-tests.ld \
        fence.S \
        -o fence
    
    log "Fence test compiled successfully"
}

# Extract existing test archive
extract_test_archive() {
    log "Extracting existing test archive"
    
    # Extract archive
    tar -xzf "${TEST_ARCHIVE}"
}

# Update test archive with fence test
update_test_archive() {
    log "Adding fence test to archive"
    
    # Copy fence test to extracted tests
    cp fence riscv-tests/
    
    # Create new archive
    tar -czf riscv-tests-new.tgz riscv-tests/
    
    # Replace original (no backup needed since we're in temp dir)
    log "Updating test archive in risc0"
    cp riscv-tests-new.tgz "${TEST_ARCHIVE}"
}

# Add fence test case to tests.rs
add_test_case() {
    log "Checking if fence test case needs to be added"
    
    # Check if fence test case already exists
    if grep -q "test_case!(fence);" "${TEST_FILE}"; then
        warn "Fence test case already exists in tests.rs"
        return
    fi
    
    log "Adding fence test case to tests.rs"
    
    # Find the line before the last test case and insert fence
    # This assumes xori is the last test before the closing brace
    sed -i '/test_case!(xori);/a\    test_case!(fence);' "${TEST_FILE}"
}

# Verify everything is set up correctly
verify_integration() {
    log "Verifying fence test integration"
    
    # Check if fence binary exists in archive
    if tar -tzf "${TEST_ARCHIVE}" | grep "riscv-tests/fence$"; then
        log "✓ Fence test found in archive"
    else
        error "✗ Fence test not found in archive"
        return 1
    fi
    
    # Check if test case exists
    if grep -q "test_case!(fence);" "${TEST_FILE}"; then
        log "✓ Fence test case found in tests.rs"
    else
        error "✗ Fence test case not found in tests.rs"
        return 1
    fi
    
    log "Fence test integration complete!"
}

# Main execution
main() {
    log "Starting fence test integration"
    
    # Check for flags
    local force_download=false
    for arg in "$@"; do
        case $arg in
            --force-download)
                force_download=true
                log "Forcing toolchain download"
                ;;
            --help)
                echo "Usage: $0 [OPTIONS]"
                echo "Options:"
                echo "  --force-download  Force download of RISC0 toolchain even if system toolchain exists"
                echo "  --help           Show this help message"
                echo ""
                echo "By default, uses system RISC-V toolchain if available (riscv64-unknown-elf-gcc)"
                exit 0
                ;;
        esac
    done
    
    # Check that source files exist
    check_prerequisites
    
    # Set up temporary working directory
    setup_temp_dir
    
    # Check for system toolchain first
    local need_download=true
    if command -v riscv64-unknown-elf-gcc &> /dev/null || command -v riscv32-unknown-elf-gcc &> /dev/null; then
        if [ "${force_download}" = false ]; then
            log "System RISC-V toolchain detected, skipping download"
            log "Use --force-download to download RISC0 toolchain anyway"
            need_download=false
        fi
    fi
    
    # Download toolchain if needed
    if [ "${need_download}" = true ]; then
        warn "GitHub releases can be very slow to download (28MB file)"
        warn "Consider installing system riscv-gnu-toolchain instead"
        warn "Or download manually and extract to ${BASE_DIR}/riscv-tests-toolchain/"
        setup_toolchain
    fi
    
    # Compile test
    compile_fence_test || {
        error "Compilation failed"
        exit 1
    }
    
    # Update test archive
    extract_test_archive
    update_test_archive
    
    # Add test case
    add_test_case
    
    # Verify
    verify_integration
    
    log "Done! You can now run: cargo test -p risc0-circuit-rv32im --features prove prove::tests::riscv::fence"
}

# Run main function
main "$@"