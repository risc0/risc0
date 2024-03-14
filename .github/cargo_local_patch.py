import argparse
import toml
import os

def modify_dependency(details, new_path):
    if 'path' not in details:
        details['path'] = new_path
        details.pop('version', None)
        details.pop('git', None)
        details.pop('rev', None)
        details.pop('branch', None)

def process_dependencies(dependencies, base_path, dep_path_mapping):
    for dep, details in dependencies.items():
        # Check if the current dependency is in our mapping
        if dep in dep_path_mapping:
            # Construct the new path using the base_path and the relative path from the mapping
            new_path = os.path.join(base_path, dep_path_mapping[dep])
            modify_dependency(details, new_path)


def calculate_base_path(cargo_toml_path):
    depth = len(os.path.normpath(cargo_toml_path).split(os.sep)) - 1
    if depth == 0:
        return "."
    else:
        return os.path.join(*[".."] * depth)

def main(cargo_toml_path, dep_path_mapping):
    base_path = calculate_base_path(cargo_toml_path)

    with open(cargo_toml_path, 'r') as file:
        data = toml.load(file)

    if 'dependencies' in data:
        dependencies = data['dependencies']
        process_dependencies(dependencies, base_path, dep_path_mapping)

    if 'workspace' in data and 'dependencies' in data['workspace']:
        process_dependencies(data['workspace']['dependencies'], base_path, dep_path_mapping)

    with open(cargo_toml_path, 'w') as file:
        toml.dump(data, file)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Modify dependencies in Cargo.toml")
    parser.add_argument("cargo_toml_path", help="Path to the Cargo.toml file to modify")
    args = parser.parse_args()

    # Define risc0, risc0-ethereum and bonsai dependencies and their paths here
    # Add more dependencies and paths as needed
    dep_path_mapping = {
        "bonsai-rest-api-mock": "../risc0/bonsai/rest-api-mock",
        "bonsai-sdk": "../risc0/bonsai/sdk",
        "risc0-binfmt": "../risc0/risc0/binfmt",
        "risc0-build": "../risc0/risc0/build",
        "risc0-build-kernel": "../risc0/risc0/build_kernel",
        "risc0-circuit-recursion": "../risc0/risc0/circuit/recursion",
        "risc0-circuit-recursion-sys": "../risc0/risc0/circuit/recursion-sys",
        "risc0-circuit-rv32im": "../risc0/risc0/circuit/rv32im",
        "risc0-circuit-rv32im-sys": "../risc0/risc0/circuit/rv32im-sys",
        "risc0-core": "../risc0/risc0/core",
        "risc0-groth16": "../risc0/risc0/groth16",
        "risc0-r0vm": "../risc0/risc0/r0vm",
        "risc0-sys": "../risc0/risc0/sys",
        "risc0-zkp": "../risc0/risc0/zkp",
        "risc0-zkvm": "../risc0/risc0/zkvm",
        "risc0-zkvm-platform": "../risc0/risc0/zkvm/platform",
        "risc0-ethereum-contracts": "../risc0-ethereum/contracts",
        "risc0-build-ethereum": "../risc0-ethereum/build",
        "risc0-forge-ffi": "../risc0-ethereum/ffi",
        "risc0-ethereum-relay": "../risc0-ethereum/relay",
    }

    main(os.path.normpath(args.cargo_toml_path), dep_path_mapping)
