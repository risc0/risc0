// @ts-check
// Note: type annotations allow type checking and IDEs autocompletion!

const lightCodeTheme = require("prism-react-renderer/themes/github");
const darkCodeTheme = require("prism-react-renderer/themes/dracula");
const math = require("remark-math");
const katex = require("rehype-katex");
const rustCode = require("./src/remark/rust");
const baseUrl = process.env.BASE_URL || "/";

/** @type {import('@docusaurus/types').Config} */
const config = {
  title: "RISC Zero Developer Docs",
  tagline: "Hyper-Efficient General Purpose Zero-Knowledge Computing.",
  favicon: "img/logo.png",

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
          editUrl: ({ locale, docPath }) => {
            // We want users to submit updates to the upstream/next version!
            // Otherwise we risk losing the update on the next release.
            const nextVersionDocsDirPath = "docs";
            return `https://github.com/risc0/risc0/edit/main/website/${nextVersionDocsDirPath}/${docPath}`;
          },
          remarkPlugins: [math, rustCode],
          rehypePlugins: [katex],
        },
        blog: {},
        pages: {},
        theme: {
          customCss: require.resolve("./src/css/custom.css"),
        },
      }),
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
      image: "img/logo.png",
      navbar: {
        title: "RISC Zero",
        logo: {
          alt: "RISC Zero Logo",
          src: "img/logo.png",
        },
        items: [
          { to: "/", label: "Introduction", position: "left" },
          {
            position: "left",
            label: "Terminology",
            to: "terminology",
          },
          {
            position: "left",
            label: "FAQ",
            to: "tech_faq",
          },
          {
            type: "docsVersionDropdown",
            position: "right",
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
        theme: lightCodeTheme,
        darkTheme: darkCodeTheme,
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

module.exports = config;
