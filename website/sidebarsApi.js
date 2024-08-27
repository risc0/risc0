// @ts-check

/** @type {import('@docusaurus/plugin-content-docs').SidebarsConfig} */
export default {
  api: [
    {
      type: "html",
      value:
        '<h4 class="sidebar-heading">LEARN <span class="sidebar-heading-divider"></span></h4>',
      defaultStyle: true,
    },
    {
      type: "doc",
      label: "Introduction",
      id: "introduction",
    },
    {
      type: "doc",
      label: "What does RISC Zero enable?",
      id: "use-cases",
    },
    {
      type: "category",
      label: "What is a zkVM Application?",
      collapsed: true,
      items: [
        {
          type: "doc",
          label: "Overview",
          id: "zkvm/zkvm-overview",
        },
        {
          type: "doc",
          label: "Receipts 101",
          id: "zkvm/receipts",
        },
        {
          type: "doc",
          label: "Guest Code 101",
          id: "zkvm/guest-code-101",
        },
        {
          type: "doc",
          label: "Host Code 101",
          id: "zkvm/host-code-101",
        },
        {
          type: "doc",
          label: "Example Applications",
          id: "zkvm/examples",
        },
      ],
    },
    {
      type: "html",
      value:
        '<h4 class="sidebar-heading">Build <span class="sidebar-heading-divider"></span></h4>',
      defaultStyle: true,
    },
    {
      type: "doc",
      label: "Getting Started",
      id: "getting-started",
    },
    {
      type: "category",
      label: "Writing your zkVM Application",
      collapsed: true,
      items: [
        {
          type: "doc",
          label: "Installation",
          id: "zkvm/install",
        },
        {
          type: "doc",
          label: "Quick Start",
          id: "zkvm/quickstart",
        },
        {
          type: "doc",
          label: "Hello World Tutorial",
          id: "zkvm/tutorials/hello-world",
        },
        {
          type: "doc",
          label: "Understanding I/O",
          id: "zkvm/tutorials/io",
        },
        {
          type: "doc",
          label: "Proof Composition",
          id: "zkvm/composition",
        },
        {
          type: "doc",
          label: "Rust Resources",
          id: "zkvm/rust-resources",
        },
        {
          type: "doc",
          label: "Rust Crates that Use C++",
          id: "zkvm/rust-crates-with-cpp",
        },
        {
          type: "link",
          label: "API Reference Docs",
          href: "https://docs.rs/risc0-zkvm/",
        },
      ],
    },
    {
      type: "category",
      label: "Generating Proofs for your zkVM Application",
      collapsed: true,
      items: [
        {
          type: "doc",
          label: "Proving Options",
          id: "generating-proofs/proving-options",
        },
        {
          type: "doc",
          label: "Dev Mode",
          id: "generating-proofs/dev-mode",
        },
        {
          type: "doc",
          label: "Local Proving",
          id: "generating-proofs/local-proving",
        },
        {
          type: "doc",
          label: "Remote Proving",
          id: "generating-proofs/remote-proving",
        },
      ],
    },
    {
      type: "category",
      label: "Optimizing your zkVM Application",
      collapsed: true,
      items: [
        {
          type: "doc",
          label: "Profiling",
          id: "zkvm/profiling",
        },
        {
          type: "doc",
          label: "Guest Optimization",
          id: "zkvm/optimization",
        },
        {
          type: "doc",
          label: "Cryptography Acceleration",
          id: "zkvm/acceleration",
        },
        {
          type: "doc",
          label: "Performance Benchmarks",
          id: "zkvm/benchmarks",
        },
      ],
    },
    {
      type: "category",
      label: "Blockchain Integration",
      collapsed: true,
      items: [
        {
          type: "doc",
          label: "Posting & Verifying Proofs on Ethereum",
          id: "blockchain-integration/bonsai-on-eth",
        },
        {
          type: "doc",
          label: "Ethereum Examples",
          id: "blockchain-integration/eth-examples",
        },
        {
          type: "doc",
          label: "Verifier Contract",
          id: "blockchain-integration/contracts/verifier",
        },
      ],
    },
    {
      type: "html",
      value:
        '<h4 class="sidebar-heading">Miscellaneous <span class="sidebar-heading-divider"></span></h4>',
      defaultStyle: true,
    },
    {
      type: "category",
      label: "Security",
      collapsed: true,
      items: [
        {
          type: "doc",
          label: "Secure Development Lifecycle",
          id: "secure-sdlc",
        },
        {
          type: "link",
          label: "Security Policy",
          href: "https://github.com/risc0/risc0/security/policy",
        },
        {
          type: "link",
          label: "Audit Reports",
          href: "https://github.com/risc0/rz-security/tree/main/audits",
        },
        {
          type: "link",
          label: "Advisories",
          href: "https://github.com/risc0/risc0/security/advisories",
        },
        {
          type: "link",
          label: "Bug Bounty",
          href: "https://hackenproof.com/programs/risc-zero-zkvm",
        },
        {
          type: "doc",
          label: "Cryptographic Security Model",
          id: "security-model",
        },
        {
          type: "doc",
          label: "Trusted Setup",
          id: "trusted-setup-ceremony",
        },
        {
          type: "link",
          label: "Verifier Version Management Design",
          href: "https://github.com/risc0/risc0-ethereum/blob/main/contracts/version-management-design.md",
        },
      ],
    },
    {
      type: "category",
      label: "zkVM Technical Reference",
      collapsed: true,
      items: [
        {
          type: "doc",
          label: "Recursion",
          id: "recursion",
        },
        {
          type: "doc",
          label: "zkVM technical specification",
          id: "zkvm/zkvm-specification",
        },
      ],
    },
    {
      type: "link",
      label: "Awesome risc0",
      href: "https://github.com/inversebrah/awesome-risc0",
    },
  ],
};
