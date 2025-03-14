import argparse
import toml
import os
import fnmatch

def find_cargo_toml_files(start_path, ignore_dirs=None):
    if ignore_dirs is None:
        ignore_dirs = []

    matches = []
    for root, dirs, filenames in os.walk(start_path):
        # Skip directories specified in ignore_dirs
        root_abs = os.path.abspath(root)
        if any(root_abs.startswith(os.path.abspath(i)) for i in ignore_dirs):
            dirs.clear()
            continue

        for filename in fnmatch.filter(filenames, 'Cargo.toml'):
            matches.append(os.path.join(root, filename))
    return matches

def is_subdirectory(path, of_directory):
    absolute_path = os.path.abspath(path)
    absolute_of_directory = os.path.abspath(of_directory)
    return absolute_path.startswith(absolute_of_directory)

def modify_dependency(details, new_path, start_directory):
    # If details is a string, it's in the simple format. Convert it to a dictionary.
    if isinstance(details, str):
        details = {'version': details}  # Convert to dictionary with version key
    # Now details is guaranteed to be a dictionary
    # Skip if the dependency uses the workspace definition
    if details.get('workspace') is not True:
        current_path = details.get('path')
        if current_path and is_subdirectory(current_path, start_directory):
            # If the current path is a subdirectory of the start_directory, do not modify it.
            return details

        details['path'] = new_path
        details.pop('version', None)
        details.pop('git', None)
        details.pop('rev', None)
        details.pop('tag', None)
        details.pop('branch', None)
    return details

# Modify the list of dependencies in-place, setting a path reference for those in the mapping.
def process_dependencies(dependencies, base_path, dep_path_mapping, start_directory):
    for dep, details in dependencies.items():
        # Check if a dep starts with "risc0-" or "bonsai-" and is not in the mapping.
        # This should make sure to patch all the dependencies or fail if new are found.
        if (dep.startswith("risc0-") or dep.startswith("bonsai-")) and dep not in dep_path_mapping:
            raise ValueError(f"Dependency '{dep}' starts with 'risc0-' or 'bonsai-' but is not in dep_path_mapping.")
        if dep in dep_path_mapping:
            new_path = os.path.join(base_path, dep_path_mapping[dep])
            if not os.path.exists(new_path):
                raise FileNotFoundError(f"The path {new_path} does not exist.")
            new_details = modify_dependency(details, new_path, start_directory)
            dependencies[dep] = new_details

def process_cargo_file(cargo_toml_path, dep_path_mapping, start_directory):
    base_path = os.path.join(os.path.dirname(os.path.realpath(__file__)), "../../")

    with open(cargo_toml_path, 'r') as file:
        data = toml.load(file)

    # Process regular dependencies
    if 'dependencies' in data:
        process_dependencies(data['dependencies'], base_path, dep_path_mapping, start_directory)
    # Process development dependencies
    if 'dev-dependencies' in data:
        process_dependencies(data['dev-dependencies'], base_path, dep_path_mapping, start_directory)
    # Process build dependencies
    if 'build-dependencies' in data:
        process_dependencies(data['build-dependencies'], base_path, dep_path_mapping, start_directory)
    # Process workspace dependencies, if present
    if 'workspace' in data and 'dependencies' in data['workspace']:
        process_dependencies(data['workspace']['dependencies'], base_path, dep_path_mapping, start_directory)

    with open(cargo_toml_path, 'w') as file:
        toml.dump(data, file)

def main(directory, dep_path_mapping, ignore_dirs):
    cargo_toml_files = find_cargo_toml_files(directory, ignore_dirs)
    for cargo_toml_path in cargo_toml_files:
        process_cargo_file(cargo_toml_path, dep_path_mapping, directory)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Modify dependencies in Cargo.toml files within a directory.")
    parser.add_argument("directory", help="Directory to search for Cargo.toml files")
    parser.add_argument("--ignore", action="append", default=[],
                        help="List of directories to ignore for patching")
    args = parser.parse_args()

    # Define risc0, risc0-ethereum and bonsai dependencies and their paths here
    # Add more dependencies and paths as needed
    dep_path_mapping = {
        "bonsai-rest-api-mock": "risc0/bonsai/rest-api-mock",
        "bonsai-sdk": "risc0/bonsai/sdk",
        "risc0-binfmt": "risc0/risc0/binfmt",
        "risc0-build": "risc0/risc0/build",
        "risc0-build-kernel": "risc0/risc0/build_kernel",
        "risc0-circuit-recursion": "risc0/risc0/circuit/recursion",
        "risc0-circuit-recursion-sys": "risc0/risc0/circuit/recursion-sys",
        "risc0-circuit-rv32im": "risc0/risc0/circuit/rv32im",
        "risc0-circuit-rv32im-sys": "risc0/risc0/circuit/rv32im-sys",
        "risc0-core": "risc0/risc0/core",
        "risc0-groth16": "risc0/risc0/groth16",
        "risc0-r0vm": "risc0/risc0/r0vm",
        "risc0-sys": "risc0/risc0/sys",
        "risc0-zkp": "risc0/risc0/zkp",
        "risc0-zkvm": "risc0/risc0/zkvm",
        "risc0-zkvm-platform": "risc0/risc0/zkvm/platform",
        "risc0-ethereum-contracts": "risc0-ethereum/contracts",
        "risc0-build-ethereum": "risc0-ethereum/build",
        "risc0-forge-ffi": "risc0-ethereum/crates/ffi",
        "risc0-steel": "risc0-ethereum/crates/steel",
        "risc0-op-steel": "risc0-ethereum/crates/op-steel",
        "risc0-aggregation": "risc0-ethereum/crates/aggregation",
    }

    main(os.path.normpath(args.directory), dep_path_mapping, args.ignore)
