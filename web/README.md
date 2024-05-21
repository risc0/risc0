# Web Monorepo 🌳

#### Before You Start

- Install [Node](https://nodejs.org/en) (≥ v20.x.x)

- Install [bun](https://bun.sh/) (≥ v1.0.33)

```sh
curl -fsSL https://bun.sh/install | bash
```

- If you're using vscode: please have the [Biome VSCode extension](https://marketplace.visualstudio.com/items?itemName=biomejs.biome) installed.

## Apps 👾

- [`benchmarks-and-reports`](./apps/benchmarks-and-reports) → [LIVE PROD URL](https://benchmarks.risczero.com)

## Packages 📦

- [`shared`](./packages/shared) → shared code between apps

## Testing

```sh
bun run test
```

## Development

```sh
bun run dev
```
