# Best Practice for VSCode

## Link the guest and host

When you are writing code in VSCode, if there is no code prompt in guest code, you can follow the procedure below to fix the problem

1. Create the .vscode/settings.json in your project root dir
2. Write the context into file
```json
{
  "rust-analyzer.linkedProjects": [
    "methods/guest/Cargo.toml", // Guest cargo.toml path
    "host/Cargo.toml" // Host cargo.toml path
  ]
}
```