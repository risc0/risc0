import argparse
import toml

def modify_dependency(details, new_path):
    """Modify the dependency details in place."""
    if 'path' not in details:
        details['path'] = new_path
        details.pop('version', None)
        details.pop('git', None)
        details.pop('rev', None)
        details.pop('branch', None)

def process_dependencies(dependencies, prefix, base_path):
    """Process dependencies that match a given prefix."""
    for dep, details in dependencies.items():
        if dep.startswith(prefix):
            new_path = f"{base_path}/{dep.replace(prefix + '-', '')}"
            modify_dependency(details, new_path)

def main(cargo_toml_path):
    with open(cargo_toml_path, 'r') as file:
        data = toml.load(file)

    if 'workspace' in data and 'dependencies' in data['workspace']:
        dependencies = data['workspace']['dependencies']
        process_dependencies(dependencies, "risc0", "../risc0/risc0")
        process_dependencies(dependencies, "bonsai", "../risc0/bonsai")

    with open(cargo_toml_path, 'w') as file:
        toml.dump(data, file)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Modify dependencies in Cargo.toml")
    parser.add_argument("cargo_toml_path", help="Path to the Cargo.toml file to modify")
    args = parser.parse_args()

    main(args.cargo_toml_path)
