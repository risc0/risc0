// @ts-check
// Note: type annotations allow type checking and IDEs autocompletion!

import { themes as prismThemes } from "prism-react-renderer";
import katex from "rehype-katex";
import math from "remark-math";
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

    markdown: {
      mermaid: true,
    },

    themes: ["@docusaurus/theme-mermaid"],

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
          createRedirects(path) {
            if (path.includes("/api/generating-proofs/remote-proving")) {
              return [
                path.replace(
                  "/api/generating-proofs/remote-proving",
                  "/bonsai",
                ),
                path.replace(
                  "/api/generating-proofs/remote-proving",
                  "/bonsai/quickstart",
                ),
              ];
            }
            if (path.includes("/api/zkvm")) {
              return [path.replace("/api/zkvm", "/zkvm")];
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
        src: "https://plausible.io/js/script.js",
        "data-domain": "risczero.com",
        defer: true,
      },
    ],

    themeConfig:
      /** @type {import('@docusaurus/preset-classic').ThemeConfig} */
      ({
        image: "img/logo.svg",
        navbar: {
          logo: {
            alt: "RISC Zero",
            src: "img/logo.svg",
            href: "https://risczero.com",
          },
          items: [
            {
              position: "left",
              label: "Introduction",
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
              class: "docsVersionDropdown",
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
          style: "dark",
          links: [{}],
          copyright: `Copyright © ${new Date().getFullYear()} RISC Zero, Inc. Built with Docusaurus.`,
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
        mermaid: {
          theme: { light: "default", dark: "dark" },
          options: {
            fontFamily: "var(--ifm-heading-font-family)",
            themeVariables: {
              fontSize: "12px",
              mainBkg: "rgba(255,255,255,0.9)",
              lineColor: "var(--ifm-color-emphasis-600)",
              nodeBorder: "var(--ifm-color-emphasis-500)",
              clusterBorder: "var(--ifm-color-emphasis-300)",
              clusterBkg: "var(--ifm-color-emphasis-200)",
            },
          },
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
