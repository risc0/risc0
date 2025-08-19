"use client";

import { Button } from "@risc0/ui/button";
import { CopyIcon } from "lucide-react";
import type { CodeBlock } from "notion-types";
import { getTextContent } from "notion-utils";
import { useRef, useState } from "react";

type CodeProps = {
  block: CodeBlock;
};

export function CodeCopyButton({ block }: CodeProps) {
  const [isCopied, setIsCopied] = useState<boolean>(false);
  const copyTimeout = useRef<number | null>(null);
  const content = getTextContent(block.properties.title);

  async function handleCopy() {
    await navigator.clipboard.writeText(content);
    setIsCopied(true);

    if (copyTimeout.current) {
      clearTimeout(copyTimeout.current);
      copyTimeout.current = null;
    }

    copyTimeout.current = setTimeout(() => {
      setIsCopied(false);
    }, 1200) as unknown as number;
  }

  return (
    <>
      <Button
        variant="secondary"
        startIcon={<CopyIcon />}
        onClick={async () => {
          await handleCopy();
        }}
      >
        Copy
      </Button>

      {isCopied && (
        <div className="notion-code-copy-tooltip">
          <div className="border-neutral-200/20">Copied</div>
        </div>
      )}
    </>
  );
}
