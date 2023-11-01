import { visit } from "unist-util-visit";

// Remove lines starting with `# `. This is code to make the doc tests pass
// but should not be displayed.
export default function plugin() {
  return function transformer(tree) {
    visit(tree, "code", (node) => {
      const langs = ["rust", "rs"];
      if (node.lang && langs.includes(node.lang)) {
        node.value = node.value
          .split("\n")
          .filter((line) => !line.startsWith("# "))
          .join("\n");
      }
    });
  };
}
