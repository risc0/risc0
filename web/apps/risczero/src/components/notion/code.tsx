"use client";

import mermaid from "mermaid";
import { useTheme } from "next-themes";
import type { CodeBlock } from "notion-types";
import { getTextContent } from "notion-utils";
import { highlightElement } from "prismjs";
import { useCallback } from "react";
import { Text } from "react-notion-x";
import { CodeCopyButton } from "./code-copy-button";

type CodeProps = {
  block: CodeBlock;
};

const LANG = Object.freeze({
  ASSEMBLY: "assembly",
  MERMAID: "mermaid",
  ARM_ASSEMBLY: "armasm",
});

export default function Code({ block }: CodeProps) {
  const { theme, resolvedTheme } = useTheme();

  if (block.properties.language[0]?.[0].toLowerCase() === LANG.ASSEMBLY) {
    block.properties.language = [[LANG.ARM_ASSEMBLY]];
  }

  const content = getTextContent(block.properties.title);
  const language = getTextContent(block.properties.language).toLowerCase();
  const { caption } = block.properties;
  const { id } = block;
  const isMermaid = language === LANG.MERMAID;
  const isDark = theme === "dark" || resolvedTheme === "dark";

  const highlightRef = useCallback((el: HTMLElement | null) => {
    if (!el) {
      return;
    }

    try {
      highlightElement(el);
    } catch (error) {
      console.warn("prismjs highlight error", error);
    }
  }, []);

  const mermaidRef = useCallback(
    (el: HTMLDivElement | null) => {
      if (!el) {
        return;
      }

      mermaid.initialize({
        theme: isDark ? "dark" : "neutral",
      });

      mermaid.render(`mermaid-${id}`, content).then(({ svg, bindFunctions }) => {
        el.innerHTML = svg;
        bindFunctions?.(el);
      });
    },
    [id, content, isDark],
  );

  return (
    <>
      <div className="notion-code">
        <div className="notion-code-copy">
          <CodeCopyButton block={block} />
        </div>

        <pre className="overflow-x-auto rounded-md">
          <code className={`language-${language}`} ref={highlightRef}>
            {content}
          </code>
        </pre>

        {isMermaid && <div className="flex justify-center" ref={mermaidRef} />}
      </div>

      {caption && (
        <figcaption className="notion-asset-caption">
          <Text value={caption} block={block} />
        </figcaption>
      )}
    </>
  );
}
