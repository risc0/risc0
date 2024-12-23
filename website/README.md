# Website

This website is built using [Docusaurus](https://docusaurus.io), a modern static website generator.

### Installation

First, [install bun] on your machine. Then, run:

```console
bun install
```

### Local Development

```console
bun run start
```

This command starts a local development server and opens up a browser window. Most changes are reflected live without having to restart the server.

### Build

```console
bun run build
```

This command generates static content into the `build` directory and can be served using any static content hosting service.

### Deployment

Using SSH:

```console
USE_SSH=true bun run deploy
```

Not using SSH:

```console
GIT_USER=<Your GitHub username> bun run deploy
```

If you are using GitHub pages for hosting, this command is a convenient way to build the website and push to the `gh-pages` branch.

[install bun]: https://bun.sh/docs/installation
