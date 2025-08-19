"use client";

// custom notion and prism styles
import "../../styles/notion.css";
import "../../styles/prism.css";

import dynamic from "next/dynamic";
import type { ComponentPropsWithoutRef } from "react";
import { NotionRenderer as Renderer } from "react-notion-x";

const Code = dynamic(() =>
  import("@/components/notion/code").then(async (m) => {
    await Promise.allSettled([
      //import("prismjs/components/prism-markup-templating.min.js"),
      //import("prismjs/components/prism-abap.min.js"),
      //import("prismjs/components/prism-agda.min.js"),
      //import("prismjs/components/prism-arduino.min.js"),
      //import("prismjs/components/prism-armasm.min.js"),
      import("prismjs/components/prism-bash.min.js"),
      //import("prismjs/components/prism-basic.min.js"),
      //import("prismjs/components/prism-bnf.min.js"),
      //import("prismjs/components/prism-c.min.js"),
      //import("prismjs/components/prism-clojure.min.js"),
      //import("prismjs/components/prism-coffeescript.min.js"),
      //import("prismjs/components/prism-coq.min.js"),
      //import("prismjs/components/prism-cpp.min.js"),
      //import("prismjs/components/prism-csharp.min.js"),
      import("prismjs/components/prism-css.min.js"),
      //import("prismjs/components/prism-glsl.min.js"),
      //import("prismjs/components/prism-go.min.js"),
      //import("prismjs/components/prism-graphql.min.js"),
      //import("prismjs/components/prism-groovy.min.js"),
      //import("prismjs/components/prism-haskell.min.js"),
      //import("prismjs/components/prism-idris.min.js"),
      //import("prismjs/components/prism-java.min.js"),
      import("prismjs/components/prism-javascript.min.js"),
      import("prismjs/components/prism-json.min.js"),
      //import("prismjs/components/prism-julia.min.js"),
      //import("prismjs/components/prism-kotlin.min.js"),
      import("prismjs/components/prism-latex.min.js"),
      //import("prismjs/components/prism-less.min.js"),
      //import("prismjs/components/prism-lisp.min.js"),
      //import("prismjs/components/prism-livescript.min.js"),
      //import("prismjs/components/prism-llvm.min.js"),
      //import("prismjs/components/prism-lua.min.js"),
      //import("prismjs/components/prism-makefile.min.js"),
      import("prismjs/components/prism-markdown.min.js"),
      //import("prismjs/components/prism-markup.min.js"),
      //import("prismjs/components/prism-matlab.min.js"),
      import("prismjs/components/prism-mermaid.min.js"),
      //import("prismjs/components/prism-nix.min.js"),
      //import("prismjs/components/prism-objectivec.min.js"),
      //import("prismjs/components/prism-ocaml.min.js"),
      //import("prismjs/components/prism-pascal.min.js"),
      //import("prismjs/components/prism-perl.min.js"),
      //import("prismjs/components/prism-php.min.js"),
      //import("prismjs/components/prism-powershell.min.js"),
      //import("prismjs/components/prism-prolog.min.js"),
      //import("prismjs/components/prism-protobuf.min.js"),
      //import("prismjs/components/prism-purescript.min.js"),
      //import("prismjs/components/prism-python.min.js"),
      //import("prismjs/components/prism-r.min.js"),
      //import("prismjs/components/prism-racket.min.js"),
      //import("prismjs/components/prism-reason.min.js"),
      //import("prismjs/components/prism-ruby.min.js"),
      import("prismjs/components/prism-rust.min.js"),
      //import("prismjs/components/prism-sass.min.js"),
      //import("prismjs/components/prism-scala.min.js"),
      //import("prismjs/components/prism-scheme.min.js"),
      //import("prismjs/components/prism-scss.min.js"),
      //import("prismjs/components/prism-shell-session.min.js"),
      import("prismjs/components/prism-solidity.min.js"),
      import("prismjs/components/prism-sql.min.js"),
      //import("prismjs/components/prism-swift.min.js"),
      import("prismjs/components/prism-toml.min.js"),
      import("prismjs/components/prism-typescript.min.js"),
      //import("prismjs/components/prism-vbnet.min.js"),
      //import("prismjs/components/prism-verilog.min.js"),
      //import("prismjs/components/prism-vhdl.min.js"),
      //import("prismjs/components/prism-visual-basic.min.js"),
      import("prismjs/components/prism-wasm.min.js"),
      import("prismjs/components/prism-xml-doc.min.js"),
      import("prismjs/components/prism-yaml.min.js"),
    ]);

    return m;
  }),
);

const components = {
  Code,
  Collection: () => <></>,
  Equation: () => <></>,
  Pdf: () => <></>,
  Tweet: () => <></>,
};

function mapPageUrl(id: string) {
  return `https://www.notion.so/${id.replaceAll("-", "")}`;
}

export function NotionRendererFull(
  props: Omit<ComponentPropsWithoutRef<typeof Renderer>, "components" | "mapPageUrl">,
) {
  return <Renderer components={components} mapPageUrl={mapPageUrl} {...props} />;
}
