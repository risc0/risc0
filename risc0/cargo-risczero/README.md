# Cargo-risczero

Cargo extension to help create, manage, and test [RISC Zero](https://github.com/risc0/risc0) projects.

## Install

```bash
## Install from crates.io
cargo install cargo-risczero
## Installing from local source
cargo install --path risc0/cargo-risczero
```

## New

The `new` command will create a new project for an existing template. It defaults to the template at [rust-starter](https://github.com/risc0/risc0/tree/main/templates/rust-starter) but can be used with other templates locally or hosted on github.

### Examples

```bash
## Create a project from the main template
cargo risczero new my_project

## Create a project with 'std' support in the guest
cargo risczero new my_project --std

## Disable git initialization
cargo risczero new my_project --no-git

## Create from github template
cargo risczero new my_project --template https://github.com/risc0/risc0-rust-starter
```