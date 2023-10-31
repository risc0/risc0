// @ts-check

/** @type {import('@docusaurus/plugin-content-docs').SidebarsConfig} */
const sidebars = {
  GettingStartedSidebar: [
    "introduction",
    {
      type: "category",
      label: "Bonsai",
      link: {
        type: `doc`,
        id: "bonsai/bonsai-overview",
      },
      collapsed: false,
      items: [
        {
          type: "doc",
          label: "Quick Start",
          id: "bonsai/quickstart",
        },
        {
          type: "doc",
          label: "Bonsai on Ethereum",
          id: "bonsai/bonsai-on-eth",
        },
        {
          type: "doc",
          label: "A Blockchain Dev's Guide to zkVM Development",
          id: "bonsai/blockchain-zkvm-guide",
        },
      ],
    },
    {
      type: "category",
      label: "zkVM",
      link: {
        type: `doc`,
        id: "zkvm/zkvm_overview",
      },
      collapsed: false,
      items: [
        {
          type: "doc",
          label: "Quick Start",
          id: "zkvm/quickstart",
        },
        {
          type: "doc",
          label: "Dev Mode",
          id: "zkvm/dev-mode",
        },
        {
          type: "link",
          label: "API Reference Docs",
          href: "https://docs.rs/risc0-zkvm/",
        },
        {
          type: "doc",
          label: "Installation",
          id: "zkvm/install",
        },
        {
          type: "doc",
          label: "Rust Resources",
          id: "zkvm/developer-guide/rust-resources",
        },
        {
          type: "doc",
          label: "Guest Code 101",
          id: "zkvm/developer-guide/guest-code-101",
        },
        {
          type: "doc",
          label: "Host Code 101",
          id: "zkvm/developer-guide/host-code-101",
        },
        {
          type: "doc",
          label: "Receipts",
          id: "zkvm/developer-guide/receipts",
        },
        {
          type: "doc",
          label: "Acceleration",
          id: "zkvm/developer-guide/acceleration",
        },
        {
          type: "doc",
          label: "Profiling",
          id: "zkvm/developer-guide/profiling",
        },
        {
          type: "doc",
          label: "Performance Benchmarks",
          id: "zkvm/benchmarks",
        },
        {
          type: "doc",
          label: "Examples",
          id: "zkvm/examples",
        },
        {
          type: "link",
          label: "Source code",
          href: "https://github.com/risc0/risc0",
        },
      ],
    },
    {
      type: "category",
      label: "Proof System",
      link: {
        type: `doc`,
        id: "proof-system/proof-system",
      },
      collapsed: false,
      items: [
        {
          type: "doc",
          label: "STARK by hand",
          id: "proof-system/stark-by-hand",
        },
        {
          type: "doc",
          label: "Sequence Diagram",
          id: "proof-system/proof-system-sequence-diagram",
        },
        {
          type: "link",
          label: "Proof System Rust Crate",
          href: "https://docs.rs/risc0-zkp/*/risc0_zkp/",
        },
        {
          type: "link",
          label: "ZKP Whitepaper",
          href: "https://www.risczero.com/proof-system-in-detail.pdf",
        },
      ],
    },
    {
      type: "category",
      label: "Additional Resources",
      collapsed: false,
      items: [
        {
          type: "link",
          label: "YouTube",
          href: "https://youtube.com/@risczero",
        },
        {
          type: "doc",
          label: "Study Club",
          id: "studyclub",
        },
        {
          type: "link",
          label: "Education Database",
          href: "https://risczero.notion.site/5a335a1d29b44cb48c44b36ae66f366f?v=95cda72e39d3403fbfb59884afb0045d&pvs=4",
        },
        {
          type: "category",
          label: "Background Reading",
          items: [
            {
              type: "doc",
              label: "Arithmetic Circuits",
              id: "reference-docs/about-arithmetic-circuits",
            },
            {
              type: "doc",
              label: "Finite Fields",
              id: "reference-docs/about-finite-fields",
            },
            {
              type: "doc",
              label: "FRI Protocol",
              id: "reference-docs/about-fri",
            },
            {
              type: "doc",
              label: "PLONK",
              id: "reference-docs/about-plonk",
            },
            {
              type: "doc",
              label: "STARKs",
              id: "reference-docs/about-starks",
            },
            {
              type: "doc",
              label: "Number Theoretic Transforms",
              id: "reference-docs/about-ntts-and-fourier",
            },
            {
              type: "doc",
              label: "RISC-V",
              id: "reference-docs/about-risc-v",
            },
            {
              type: "doc",
              label: "Reed Solomon Codes",
              id: "reference-docs/about-rs-codes",
            },
          ],
        },
      ],
    },
    {
      type: "category",
      label: "Contribute to RISC Zero",
      items: [
        {
          type: "doc",
          label: "Contributor guide",
          id: "contributors-guide",
        },
        {
          type: "link",
          label: "Risc Zero Github",
          href: "https://github.com/risc0/risc0",
        },
      ],
    },
  ],
};

module.exports = sidebars;
