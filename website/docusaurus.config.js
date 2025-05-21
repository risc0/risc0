// @ts-check
// Note: type annotations allow type checking and IDEs autocompletion!

import { themes as prismThemes } from "prism-react-renderer";
import katex from "rehype-katex";
import math from "remark-math";
import apiVersions from "./api_versions.json";
import rustCode from "./src/remark/rust.js";

const baseUrl = process.env.BASE_URL ?? "/";

export default async function createConfigAsync() {
  /** @type {import('@docusaurus/types').Config} */
  return {
    title: "RISC Zero Developer Docs",
    tagline: "Hyper-Efficient General Purpose Zero-Knowledge Computing.",
    favicon: "img/favicon.ico",

    url: "https://dev.risczero.com",
    baseUrl: baseUrl,

    organizationName: "risc0",
    projectName: "devdocs",

    onBrokenLinks: "throw",
    onBrokenMarkdownLinks: "throw",

    i18n: {
      defaultLocale: "en",
      locales: ["en"],
    },

    future: {
      experimental_faster: {
        swcJsLoader: true,
        swcJsMinimizer: true,
        swcHtmlMinimizer: false, // doesn't work with @acid-info/docusaurus-og
        lightningCssMinimizer: true,
        rspackBundler: true,
        mdxCrossCompilerCache: true,
      },
    },

    presets: [
      [
        "classic",
        /** @type {import('@docusaurus/preset-classic').Options} */
        ({
          docs: {
            routeBasePath: "/",
            sidebarPath: require.resolve("./sidebars.js"),
            remarkPlugins: [math, rustCode],
            rehypePlugins: [katex],
          },
          blog: false,
          pages: {},
          theme: {
            customCss: require.resolve("./src/css/custom.css"),
          },
        }),
      ],
    ],

    plugins: [
      [
        "@acid-info/docusaurus-og",
        {
          path: "./preview-images", // relative to the build directory
          imageRenderers: {
            "docusaurus-plugin-content-docs": require("./src/og/og-renderer")
              .renderer,
          },
        },
      ],
      [
        "@docusaurus/plugin-content-docs",
        {
          id: "api",
          path: "api",
          routeBasePath: "api",
          sidebarPath: "./sidebarsApi.js",
          remarkPlugins: [math, rustCode],
          rehypePlugins: [katex],
          editUrl: ({ locale, docPath }) => {
            // We want users to submit updates to the upstream/next version!
            // Otherwise we risk losing the update on the next release.
            return `https://github.com/risc0/risc0/edit/main/website/api/${docPath}`;
          },
        },
      ],
      [
        "@docusaurus/plugin-client-redirects",
        {
          createRedirects(existingPath) {
            if (
              existingPath.includes("/api/generating-proofs/remote-proving")
            ) {
              return [
                existingPath.replace(
                  "/api/generating-proofs/remote-proving",
                  "/bonsai",
                ),
                existingPath.replace(
                  "/api/generating-proofs/remote-proving",
                  "/bonsai/quickstart",
                ),
              ];
            }
            if (existingPath.includes("/zkvm/precompiles")) {
              return [
                existingPath.replace("/zkvm/precompiles", "/zkvm/acceleration"),
              ];
            }
            if (existingPath.includes("/zkvm/developer-guide/precompiles")) {
              return [
                existingPath.replace(
                  "/zkvm/developer-guide/precompiles",
                  "/zkvm/developer-guide/acceleration",
                ),
              ];
            }

            if (existingPath.includes("/api/zkvm")) {
              return [existingPath.replace("/api/zkvm", "/zkvm")];
            }

            if (existingPath.includes("/api")) {
              return [existingPath.replace("/api", `/api/${apiVersions[0]}`)];
            }

            return undefined;
          },
          redirects: [{ from: "/tech_faq", to: "/faq" }],
        },
      ],
    ],

    stylesheets: [
      {
        href: "https://cdn.jsdelivr.net/npm/katex@0.13.24/dist/katex.min.css",
        type: "text/css",
        integrity:
          "sha384-odtC+0UGzzFL/6PNoE8rX/SPcQDXBJ+uRepguP4QkPCm2LBxH3FA3y+fKSiJ+AmM",
        crossorigin: "anonymous",
      },
    ],

    scripts: [
      {
        src: "https://plausible.io/js/script.outbound-links.js",
        "data-domain": "dev.risczero.com",
        defer: true,
      },
    ],

    themeConfig:
      /** @type {import('@docusaurus/preset-classic').ThemeConfig} */
      ({
        metadata: [
          { name: "twitter:card", content: "summary_large_image" },
          { name: "og:type", content: "website" },
          { name: "og:logo", content: "img/logo.svg" },
        ],
        navbar: {
          logo: {
            alt: "RISC Zero",
            src: "img/logo.svg",
            href: "/",
          },
          items: [
            {
              position: "left",
              label: "Documentation",
              to: "/api",
            },
            {
              position: "left",
              label: "Terminology",
              to: "/terminology",
            },
            {
              position: "left",
              label: "FAQ",
              to: "/faq",
            },
            {
              position: "left",
              label: "Education Hub",
              to: "/education",
            },
            {
              type: "docsVersionDropdown",
              position: "right",
              docsPluginId: "api",
              className: "docsVersionDropdown",
            },
            {
              href: "https://www.risczero.com/blog",
              position: "right",
              label: "Blog",
            },
            {
              href: "https://github.com/risc0",
              position: "right",
              label: "GitHub",
            },
            {
              type: "dropdown",
              position: "right",
              label: "Community",
              items: [
                {
                  label: "Discord",
                  href: "https://discord.gg/risczero",
                },
                {
                  label: "Twitter",
                  href: "https://twitter.com/risczero",
                },
                {
                  label: "YouTube",
                  href: "https://www.youtube.com/@risczero",
                },
                {
                  label: "Stack Overflow",
                  href: "https://stackoverflow.com/questions/tagged/risczero",
                },
                {
                  label: "Contributor's Guide",
                  to: "contributors-guide",
                },
              ],
            },
          ],
        },
        footer: {
          logo: {
            alt: "RISC Zero",
            src: "img/logo.svg",
            href: "https://risczero.com",
            height: 42,
          },
          links: [
            {
              items: [
                {
                  label: "Blog",
                  href: "https://www.risczero.com/blog",
                },
                {
                  label: "Careers",
                  href: "https://jobs.ashbyhq.com/RiscZero",
                },
                {
                  label: "Reports & Benchmarks",
                  href: "https://reports.risczero.com",
                },
                {
                  label: "Bug Bounties",
                  href: "https://hackenproof.com/company/risc-zero/programs",
                },
              ],
            },
            {
              items: [
                {
                  label: "GitHub",
                  href: "https://github.com/risc0",
                },
                {
                  label: "Discord",
                  href: "https://discord.com/invite/risczero",
                },
                {
                  label: "X",
                  href: "https://x.com/RiscZero",
                },
                {
                  label: "YouTube",
                  href: "https://www.youtube.com/@risczero",
                },
              ],
            },
          ],
          copyright: `©${new Date().getFullYear()} RISC Zero`,
        },
        prism: {
          additionalLanguages: ["bash", "rust", "toml"],
          theme: prismThemes.github,
          darkTheme: prismThemes.dracula,
        },
        colorMode: {
          defaultMode: "dark",
          respectPrefersColorScheme: false,
        },
        algolia: {
          appId: "TQC8F4X8Z5",
          apiKey: "96f324a5e3029cd7b5ba98c91068a7a3", // Public API key
          indexName: "risczero",
          searchPagePath: "search",

          // Leaving at the default of `true` for now
          contextualSearch: true,
        },
      }),
  };
}
