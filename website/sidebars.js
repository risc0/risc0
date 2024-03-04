// @ts-check

/** @type {import('@docusaurus/plugin-content-docs').SidebarsConfig} */
export default {
  education_hub: [
    {
      type: "link",
      label: "Talks and Podcasts",
      href: "https://www.youtube.com/playlist?list=PLcPzhUaCxlCgCvzkkaBWzVuHdBRsTNxj1",
    },
    {
      type: "link",
      label: "Articles",
      href: "https://risczero.com/blog",
    },
    "studyclub",
    {
      type: "link",
      label: "Education Database",
      href: "https://risczero.notion.site/5a335a1d29b44cb48c44b36ae66f366f?v=95cda72e39d3403fbfb59884afb0045d&pvs=4",
    },
    {
      type: "category",
      label: "Proof System",
      link: {
        type: "doc",
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
          label: "ZKP Whitepaper",
          href: "https://www.risczero.com/proof-system-in-detail.pdf",
        },
      ],
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
};
