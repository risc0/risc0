# Contributor's Guide

_This page describes guidelines for community contributions to this [website](https://github.com/risc0/risc0/tree/main/website); you may also be interested in contributing to the [main project codebase](https://github.com/risc0/risc0)._

> `RISC Zero welcomes community participation!`
>
> - Make suggestions or report bugs via [GitHub issues](https://github.com/risc0/risc0/issues)
> - Contribute website content or give feedback on [open pull requests](https://github.com/risc0/risc0/pulls)
> - Contribute to the [main zkVM project](https://github.com/risc0/risc0) (see [CONTRIBUTING](https://github.com/risc0/risc0/blob/main/CONTRIBUTING.md))
> - Contribute to our tutorials and how-to guides for our [templates](https://github.com/risc0/risc0/tree/main/risc0/cargo-risczero/templates) and [Rust examples](https://github.com/risc0/risc0/tree/main/examples)
> - Ask questions on [Discord](https://discord.gg/risczero)

## How To Contribute

- All changes to this website are managed through GitHub pull requests, so you'll need a [GitHub Account](https://github.com) to contribute.
- You can suggest an edit directly via the `Edit this Page` button at the bottom of each page.
- To create a new page, you can use the [GitHub browser interface](https://github.com/risc0/risc0/tree/main/website); the content is in `src/pages` and `docs`.
  - Please read about [the navbar and sidebars](./contributors-guide.md#navbar-and-sidebars) before creating a new page.
- If you want to clone the repository and work locally, you may want to check out the [Docusaurus documentation](https://docusaurus.io/docs/installation).
  We like to use `bun run start` to run a local build, especially when we're working with changes that involve links or sidebars.

## Style Guidelines

Our objective in organizing and creating website content is that anyone who finds their way to any RISC Zero content is able to rapidly find their way to the material suits their needs.

In order to achieve this objective, we rely on:

> - `Clear Purpose`: We aim for single-purpose docs, and we head each document with a succinct statement of purpose and pointers to related content.
>   We use roadmaps, signposting, headings, and text formatting to guide the reader's attention toward the purpose of the doc.
> - `Keep it Simple`: We write short sentences with minimal superfluous language.
>   We keep content digestible by splitting long docs into smaller chunks.
> - `Progressive Disclosure`: Our landing pages are simple and clear.
>   Both at the level of site-organization and individual doc-organization, we present a bird's eye view first with opt-in paths toward higher levels of detail and technicality.
> - `Lots of Pointers`: We keep materials succinct through extensive use of pointers on modular, single-purpose components.
> - `Consistent and Accessible Terminology`: We are diligent about using our official terminology as defined and using precise language as much as possible.
>   At the same time, we minimize our use of technical jargon, taking care to provide reference pages to pre-requisite knowledge as appropriate.

## Terminology Conventions

[`RISC Zero Official Terminology`](./terminology.md)

Our terminology and naming conventions are subject to ongoing evaluation, and we encourage conversation and questions on these topics.
Please let us know via a [`GitHub issue`](https://github.com/risc0/risc0/issues) when you encounter terms that don't seem quite right.

## Navbar and Sidebars

- The navbar is defined in `docusaurus.config.js`. Any changes require manual configuration.
  - [How to edit the navbar](https://docusaurus.io/docs/api/docusaurus-config)
- The sidebars are defined in `sidebars.js`. Any new docs require manual configuration.
  - [How to edit the sidebar](https://docusaurus.io/docs/sidebar)
  - The default configuration (and our current configuration) is that `pages` do not have sidebars and `docs` do.

### Reference Docs

We typically organize reference docs according to the following sections; we use `About NTTs` as a template.

> **Topic**
>
> _Topic is used to \[concise explanation of relevance to RISC Zero]_
>
> - Documentation
> - Basic Function
> - Content 1
> - Content 2
> - Content 3
> - Suggested Reading

_Changes to this organization can be proposed for discussion via a [GitHub issue](https://github.com/risc0/risc0/issues) or proposed for action via a PR on this page._

### Explainer Docs

Our explainer docs are currently split into `zkVM Explainers` and `ZKP Explainers`.
Explainers contain clearly articulated goals in the header, as well as pointers to related content.

## Thank you!

We're excited about the engagement we've seen so far, and we're looking forward to building a vibrant community together.

## Questions?

Find us on [Discord](https://discord.gg/risczero).
