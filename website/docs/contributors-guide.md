# Contributor's Guide

_This page describes guidelines for community contributions to this [website][7]; you may also be interested in contributing to the [main project codebase][0]._

> `RISC Zero welcomes community participation!`
>
> - Make suggestions or report bugs via [GitHub issues][1]
> - Contribute website content or give feedback on [open pull requests][2]
> - Contribute to the [main zkVM project][0]
> - Contribute to our tutorials and how-to guides for our [templates](https://github.com/risc0/risc0/tree/main/templates) and [Rust examples][4]
> - Ask questions on [Discord][5]

## How To Contribute

- All changes to this website are managed through GitHub pull requests, so you'll need a [GitHub Account][6] to contribute.
- You can suggest an edit directly via the `Edit this Page` button at the bottom of each page.
- To create a new page, you can use the [GitHub browser interface][7]; the content is in `src/pages` and `docs`.
  - Please read about [the navbar and sidebars](./contributors-guide.md#navbar-and-sidebars) and [categories of documentation][8] before creating a new page.
- If you want to clone the repository and work locally, you may want to check out the [Docusaurus documentation][9].
  We like to use `yarn start` to run a local build, especially when we're working with changes that involve links or sidebars.

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

[`RISC Zero Official Terminology`][10]

Our terminology and naming conventions are subject to ongoing evaluation, and we encourage conversation and questions on these topics.
Please let us know via a [`GitHub issue`][1] when you encounter terms that don't seem quite right.

## Navbar and Sidebars

- The navbar is defined in `docusaurus.config.js`. Any changes require manual configuration.
  - [How to edit the navbar][12]
- The sidebars are defined in `sidebars.js`. Any new docs require manual configuration.
  - [How to edit the sidebar][13]
  - The default configuration (and our current configuration) is that `pages` do not have sidebars and `docs` do.

### Reference Docs

We typically organize reference docs according to the following sections; we use `About NTTs` as a template.

> **Topic**
>
> _Topic is used to [concise explanation of relevance to RISC Zero]_
>
> - Documentation
> - Basic Function
> - Content 1
> - Content 2
> - Content 3
> - Suggested Reading

_Changes to this organization can be proposed for discussion via a [GitHub issue][1] or proposed for action via a PR on this page._

### Explainer Docs

Our explainer docs are currently split into `zkVM Explainers` and `ZKP Explainers`.
Explainers contain clearly articulated goals in the header, as well as pointers to related content.

## Thank you!

We're excited about the engagement we've seen so far, and we're looking forward to building a vibrant community together.

## Questions?

Find us on [Discord][5].

[0]: https://github.com/risc0/risc0
[1]: https://github.com/risc0/website/issues
[2]: https://github.com/risc0/website/pulls
[3]: https://github.com/risc0/risc0
[4]: https://github.com/risc0/risc0/tree/v0.18.0/examples
[5]: https://discord.gg/risczero
[6]: https://github.com
[7]: https://www.github.com/risc0/website
[8]: ./contributors-guide.md#categories-of-documentation
[9]: https://docusaurus.io/docs/installation
[10]: ./terminology.md
[11]: https://github.com/risc0/website/issues
[12]: https://docusaurus.io/docs/api/docusaurus-config
[13]: https://docusaurus.io/docs/sidebar
[14]: https://github.com/risc0/website/issues
[15]: https://discord.gg/risczero
