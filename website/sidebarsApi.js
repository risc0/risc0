// @ts-check

/** @type {import('@docusaurus/plugin-content-docs').SidebarsConfig} */
export default {
  api: [
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
          id: "zkvm/dev-mode"
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
  ],
};
