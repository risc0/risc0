const url = require("node:url");
const path = require("node:path");
const fs = require("node:fs");

// this is a hand-written remark plugin that adds the .md extension to links that point to markdown files
// if it becomes annoying/wrong, we can always remove it
// if you end up removing it, also delete the `"./remark-append-md.js",` line from `package.json`
module.exports = function remarkAppendMd() {
  return function transformer(tree, file) {
    const baseDir = path.dirname(file.path);

    for (const node of tree.children) {
      if (node.type === "definition") {
        const parsedUrl = url.parse(node.url);

        // Check if the URL is internal and doesn't already have an extension
        if (!parsedUrl.protocol && !path.extname(parsedUrl.pathname || "")) {
          // Separate the path and the fragment (if any)
          const [urlPath, fragment] = (parsedUrl.pathname || "").split("#");

          let newPath = urlPath;
          // Process if the path is not empty and doesn't end with '/'
          if (urlPath && !urlPath.endsWith("/")) {
            let fullPath;

            if (!urlPath.startsWith("/")) {
              // Relative path
              fullPath = path.resolve(baseDir, urlPath);
            }

            const mdPath = `${fullPath}.md`;

            if (fs.existsSync(mdPath) && fs.statSync(mdPath).isFile()) {
              newPath += ".md";
            }
          }

          // Reattach the fragment if it exists
          if (fragment) {
            newPath += `#${fragment}`;
          }

          // Reconstruct the URL
          node.url = url.format({
            ...parsedUrl,
            pathname: newPath,
            search: null,
            path: null,
          });
        }
      }
    }
  };
};
