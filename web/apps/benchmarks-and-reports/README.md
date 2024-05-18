# Reports

## Getting Started 🚀

We need to install `bun` with:

```sh
curl -fsSL https://bun.sh/install | bash
```

Then run:

```sh
bun install      # installs all dependencies
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
