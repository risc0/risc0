# Reports

## Getting Started 🚀

> [!IMPORTANT]  
> Create an `.env` file at the root of the project and fill its contents (see `.env.example`)

Then run:

```sh
bun install      # installs all dependencies
bun run codegen  # generates types
```

## Running Tests 🧪

```sh
bun run test # will run tests against all *.test.* and *.spec.* files
```

## Analyzing Bundle Size 🤓

If you're curious about bundle size and what dependencies actually end up in production:

```sh
bun run build:analyze
```
