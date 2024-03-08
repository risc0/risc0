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

def process_dependencies(dependencies, base_path):
    for dep, details in dependencies.items():
        prefix = None
        path = None
        if dep.startswith("risc0-ethereum"):
            prefix = "risc0-ethereum"
            path = os.path.join(base_path, "../risc0-ethereum")
        elif dep.startswith("risc0"):
            prefix = "risc0"
            path = os.path.join(base_path,"../risc0/risc0")
        elif dep.startswith("bonsai"):
            prefix = "bonsai"
            path = os.path.join(base_path,"../risc0/bonsai")

        if prefix:
            new_path = os.path.join(path, dep.replace(prefix + '-', ''))
            modify_dependency(details, new_path)

def calculate_base_path(cargo_toml_path):
    depth = len(os.path.normpath(cargo_toml_path).split(os.sep)) - 1
    if depth == 0:
        return "."
    else:
        return os.path.join(*[".."] * depth)

def main(cargo_toml_path):
    base_path = calculate_base_path(cargo_toml_path)

    with open(cargo_toml_path, 'r') as file:
        data = toml.load(file)

    if 'dependencies' in data:
        dependencies = data['dependencies']
        process_dependencies(dependencies, base_path)

    if 'workspace' in data and 'dependencies' in data['workspace']:
        process_dependencies(data['workspace']['dependencies'], base_path)

    with open(cargo_toml_path, 'w') as file:
        toml.dump(data, file)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Modify dependencies in Cargo.toml")
    parser.add_argument("cargo_toml_path", help="Path to the Cargo.toml file to modify")
    args = parser.parse_args()

    main(os.path.normpath(args.cargo_toml_path))
