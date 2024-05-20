"use client";

import { useMounted } from "@risc0/ui/hooks/use-mounted";
import { default as ASCII } from "react-rainbow-ascii";

export function TextToAscii({ text, rainbow = false }: { rainbow?: boolean; text: string }) {
  const mounted = useMounted();

  return (
    <>
      <span className="sr-only">{text}</span>
      <div className="min-h-[72px] animate-fade-in">{mounted && <ASCII rainbow={rainbow} text={text} />}</div>
    </>
  );
}
