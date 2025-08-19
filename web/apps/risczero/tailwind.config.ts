import tailwindConfig from "@risc0/ui/config/tailwind.config.base";
import deepmerge from "deepmerge";
import type { Config } from "tailwindcss";
import plugin from "tailwindcss/plugin";

export const convertRemToEm = plugin(({ addVariant }) => {
  // @ts-expect-error no type
  addVariant("em", ({ container }) => {
    container.walkRules((rule) => {
      rule.selector = `.em\\:${rule.selector.slice(1)}`;
      rule.walkDecls((decl) => {
        decl.value = decl.value.replace("rem", "em");
      });
    });
  });
});

const config = deepmerge(tailwindConfig, {
  safelist: [
    "border-blobstream-light",
    "bg-blobstream-light",
    "text-blobstream-light",
    "outline-blobstream-light",
    "dark:border-blobstream-dark",
    "dark:bg-blobstream-dark",
    "dark:text-blobstream-dark",
    "dark:outline-blobstream-dark",

    "border-zeth-light",
    "bg-zeth-light",
    "text-zeth-light",
    "outline-zeth-light",
    "dark:border-zeth-dark",
    "dark:bg-zeth-dark",
    "dark:text-zeth-dark",
    "dark:outline-zeth-dark",

    "border-steel-light",
    "bg-steel-light",
    "text-steel-light",
    "outline-steel-light",
    "dark:border-steel-dark",
    "dark:bg-steel-dark",
    "dark:text-steel-dark",
    "dark:outline-steel-dark",

    "border-bonsai-light",
    "bg-bonsai-light",
    "text-bonsai-light",
    "outline-bonsai-light",
    "dark:border-bonsai-dark",
    "dark:bg-bonsai-dark",
    "dark:text-bonsai-dark",
    "dark:outline-bonsai-dark",

    "border-op-kailua-light",
    "bg-op-kailua-light",
    "text-op-kailua-light",
    "outline-op-kailua-light",
    "dark:border-op-kailua-dark",
    "dark:bg-op-kailua-dark",
    "dark:text-op-kailua-dark",
    "dark:outline-op-kailua-dark",
  ],
  theme: {
    container: {
      padding: "2rem",
    },
    extend: {
      fontFamily: {
        sans: [
          "var(--font-europa-sans)",
          "system-ui",
          "-apple-system",
          "BlinkMacSystemFont",
          "Segoe UI",
          "Helvetica",
          "Apple Color Emoji",
          "Arial",
          "sans-serif",
        ],
        mono: ["var(--font-jetbrains-mono)", "monospace"],
      },
      backgroundColor: {
        newspaper: "#F0EDE4",
        "op-kailua": {
          dark: "#FF937B",
          light: "#FF937B",
        },
        bonsai: {
          dark: "#a2a7d4",
          light: "#7a81c1",
        },
        blobstream: {
          dark: "#FF937B",
          light: "#FF937B",
        },
        steel: {
          dark: "#A6F4FF",
          light: "#00b4cd",
        },
        zeth: {
          dark: "#FF7BFA",
          light: "#ff67f9",
        },
        code: {
          light: "rgba(255,255,255,0.3)",
          dark: "rgba(255,255,255,0.03)",
        },
      },
      ringOffsetColor: {
        newspaper: "#F0EDE4",
        "op-kailua": {
          dark: "#FF937B",
          light: "#FF937B",
        },
        bonsai: {
          dark: "#a2a7d4",
          light: "#7a81c1",
        },
        blobstream: {
          dark: "#FF937B",
          light: "#FF937B",
        },
        steel: {
          dark: "#A6F4FF",
          light: "#00b4cd",
        },
        zeth: {
          dark: "#FF7BFA",
          light: "#ff67f9",
        },
      },
      outlineColor: {
        bonsai: {
          dark: "#a2a7d4",
          light: "#7a81c1",
        },
        "op-kailua": {
          dark: "#FF937B",
          light: "#FF937B",
        },
        blobstream: {
          dark: "#FF937B",
          light: "#FF937B",
        },
        steel: {
          dark: "#A6F4FF",
          light: "#00b4cd",
        },
        zeth: {
          dark: "#FF7BFA",
          light: "#ff67f9",
        },
      },
      borderColor: {
        bonsai: {
          dark: "#a2a7d4",
          light: "#7a81c1",
        },
        "op-kailua": {
          dark: "#FF937B",
          light: "#FF937B",
        },
        blobstream: {
          dark: "#FF937B",
          light: "#FF937B",
        },
        steel: {
          dark: "#A6F4FF",
          light: "#00b4cd",
        },
        zeth: {
          dark: "#FF7BFA",
          light: "#ff67f9",
        },
      },
      textColor: {
        default: {
          dark: "hsl(60 9.1% 97.8%)",
          light: "hsl(20 14.3% 4.1%)",
        },
        "op-kailua": {
          dark: "#FF937B",
          light: "#FF937B",
        },
        bonsai: {
          dark: "#a2a7d4",
          light: "#7a81c1",
        },
        blobstream: {
          dark: "#FF937B",
          light: "#FF937B",
        },
        steel: {
          dark: "#A6F4FF",
          light: "#00b4cd",
        },
        zeth: {
          dark: "#FF7BFA",
          light: "#ff67f9",
        },
        newspaper: "#F0EDE4",
      },
      animation: {
        marquee: "marquee var(--duration) linear infinite",
        "marquee-vertical": "marquee-vertical var(--duration) linear infinite",
      },
      keyframes: {
        marquee: {
          from: { transform: "translateX(0)" },
          to: { transform: "translateX(calc(-100% - var(--gap)))" },
        },
        "marquee-vertical": {
          from: { transform: "translateY(0)" },
          to: { transform: "translateY(calc(-100% - var(--gap)))" },
        },
        "shine-pulse": {
          "0%": {
            "background-position": "0% 0%",
          },
          "50%": {
            "background-position": "100% 100%",
          },
          to: {
            "background-position": "0% 0%",
          },
        },
      },
    },
  },
  plugins: [
    convertRemToEm,
    ({ addUtilities }) => {
      addUtilities({
        ".fade-bottom::after": {
          content: '""',
          position: "absolute",
          bottom: "0",
          left: "0",
          right: "0",
          height: "300px",
          background: "linear-gradient(to bottom, transparent, hsl(var(--background)))",
          pointerEvents: "none",
        },
      });
    },
  ],
}) satisfies Config;

config.content = [
  "../../packages/shared/**/*.{ts,tsx,js,jsx,mdx}",
  "../../node_modules/@risc0/ui/*.{ts,tsx,js,jsx,mdx}",
  "./src/**/*.{js,jsx,ts,tsx,mdx}",
];

export default config;
