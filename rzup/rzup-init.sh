#!/usr/bin/env bash
# Copyright 2024 RISC Zero, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set -euo pipefail

# Example URLs:
# for a 64-bit Linux system (x86_64):
# BASE_URL/rzup-x86_64-linux
# for a 64-bit macOS system (arm64):
# BASE_URL/rzup-arm64-darwin

# NOTE: Temporary release URL
RZUP_BINARY_UPDATE_ROOT="${RZUP_BINARY_UPDATE_ROOT:-https://github.com/hmrtn/asset-test/releases/download/test1/}"
QUIET=no

CARGO_BIN_DIR="${HOME}/.cargo/bin"
DEPRECATED_RISC0_DIR="${HOME}/.risc0"

usage() {
  cat <<EOF
rzup-init

The installer for rzup, from RISC Zero.

Usage: rzup-init.sh [OPTIONS]

Options:
  -v, --verbose
          Enable verbose output
  -q, --quiet
          Disable progress output
  -h, --help
          Print help
EOF
}

cleanup() {
  [ -n "${_dir:-}" ] && [ -d "$_dir" ] && rm -rf "$_dir"
}

trap cleanup EXIT

main() {
  downloader --check
  need_cmd uname
  need_cmd mktemp
  need_cmd chmod
  need_cmd mkdir
  need_cmd rm
  need_cmd rmdir
  need_cmd mv

  check_rust_installed
  get_architecture

  _arch="$RETVAL"
  assert_nz "$_arch" "arch"

  _url="${RZUP_BINARY_UPDATE_ROOT}/rzup-${_arch}"
  _dir="$(ensure mktemp -d)"
  _file="${_dir}/rzup"

  [ -f "$DEPRECATED_RISC0_DIR/bin/rzup" ] && rm -rf "$DEPRECATED_RISC0_DIR"
  [ -f "$CARGO_BIN_DIR/rzup" ] && rm "$CARGO_BIN_DIR/rzup"

  for arg in "$@"; do
    case "$arg" in
    --help)
      usage
      exit 0
      ;;
    -q | --quiet) QUIET=yes ;;
    *) ;;
    esac
  done

  info 'Downloading installer'

  ensure mkdir -p "$_dir"
  ensure downloader "$_url" "$_file"
  ensure chmod u+x "$_file"
  [ ! -x "$_file" ] && err "Cannot execute $_file"

  ensure mkdir -p "$CARGO_BIN_DIR"
  ensure mv "$_file" "$CARGO_BIN_DIR"

  info "rzup has been installed to $CARGO_BIN_DIR"
  update_path

  info "🎉 rzup installed!"
  echo "Run the following commands to install the zkVM:"
  echo "  source ${PROFILE}"
  echo "  rzup install"
}

check_rust_installed() {
  check_cmd rustc || err "Rust is not installed. Please install Rust from https://rustup.rs/ and run this script again."
}

get_architecture() {
  _ostype="$(uname -s)"
  _cputype="$(uname -m)"

  case "$_ostype" in
  Linux) _ostype=linux ;;
  Darwin) _ostype=darwin ;;
  *) err "Unsupported OS type: $_ostype" ;;
  esac

  case "$_cputype" in
  x86_64 | amd64) _cputype=x86_64 ;;
  aarch64 | arm64) _cputype=arm64 ;;
  *) err "Unsupported CPU type: $_cputype" ;;
  esac

  _arch="${_cputype}-${_ostype}"
  RETVAL="$_arch"
}

update_path() {
  detect_shell
  if [[ ":$PATH:" != *":${CARGO_BIN_DIR}:"* ]]; then
    info "Adding rzup to PATH in ${PROFILE}"
    case "$PREF_SHELL" in
    fish) echo "set -x PATH \$PATH $CARGO_BIN_DIR" >>"$PROFILE" ;;
    *) echo "export PATH=\"\$PATH:$CARGO_BIN_DIR\"" >>"$PROFILE" ;;
    esac
    info "Run the following commands to update your shell:"
    info "source ${PROFILE}"
    info "rzup"
  else
    info "rzup is already in your PATH"
  fi
}

detect_shell() {
  case $SHELL in
  */zsh)
    PROFILE="${ZDOTDIR:-"$HOME"}/.zshrc"
    PREF_SHELL='zsh'
    ;;
  */bash)
    PROFILE="$HOME/.bashrc"
    PREF_SHELL='bash'
    ;;
  */fish)
    PROFILE="$HOME/.config/fish/config.fish"
    PREF_SHELL='fish'
    ;;
  */ash)
    PROFILE="$HOME/.profile"
    PREF_SHELL='ash'
    ;;
  *) err "Could not detect shell, manually add ${CARGO_BIN_DIR} to your PATH." ;;
  esac
  info "Detected your preferred shell as ${PREF_SHELL}"
}

info() {
  [ "$QUIET" = "no" ] && printf 'info: %s\n' "$1" >&2
}

err() {
  printf 'error: %s\n' "$1" >&2
  exit 1
}

warn() {
  printf 'warn: %s\n' "$1" >&2
}

need_cmd() {
  check_cmd "$1" || err "Command not found: $1"
}

check_cmd() {
  command -v "$1" >/dev/null 2>&1
}

assert_nz() {
  [ -z "$1" ] && err "$2"
}

ensure() {
  "$@" || err "Command failed: $*"
}

downloader() {
  if [ "$1" = --check ]; then
    check_cmd curl || check_cmd wget || err "Need 'curl' or 'wget' (neither found)"
  else
    _url="$1"
    _file="$2"
    if check_cmd curl; then
      curl --silent --show-error --fail --location "$_url" --output "$_file" || err "Failed to download with curl"
    elif check_cmd wget; then
      wget --quiet --output-document="$2" "$1" || err "Failed to download with wget"
    else
      err "Need 'curl' or 'wget' (neither command found)"
    fi
  fi
}

main "$@" || exit 1
