import risc0UiConfig from "@risc0/ui/config/tailwind.config";
import type { Config } from "tailwindcss";

const config = {
  ...risc0UiConfig,
  content: ["./node_modules/@risc0/ui/**/*.{ts,tsx}", "./**/*.{ts,tsx}"],
} satisfies Config;

export default config;
