import tailwindConfig from "@risc0/ui/config/tailwind.config";
import deepmerge from "deepmerge";

const config = deepmerge(tailwindConfig, {
  theme: {
    extend: {
      fontFamily: {
        sans: ["var(--font-europa-sans)"],
        mono: ["var(--font-jetbrains-mono)"],
      },
    },
  },
});

export default config;
