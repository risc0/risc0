import filterOrder from "@joshdavenport/tailwindcss-filter-order";
import tailwindConfig from "@risc0/ui/config/tailwind.config.base";
import deepmerge from "deepmerge";
import type { Config } from "tailwindcss";

const config = deepmerge(tailwindConfig, {
  theme: {
    extend: {
      filterOrder: {
        "colored-svg-filter-order": "brightness sepia hue-rotate saturate",
      },
      fontFamily: {
        sans: ["var(--font-europa-sans)", "system-ui"],
        mono: ["var(--font-jetbrains-mono)"],
        "mono-raw": ["monospace"],
      },
    },
  },
  plugins: [filterOrder],
}) satisfies Config;

export default config;
