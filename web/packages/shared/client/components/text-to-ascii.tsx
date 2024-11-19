"use client";

import { useIsMounted } from "@risc0/ui/hooks/use-is-mounted";
import { default as ASCII } from "react-rainbow-ascii";

export function TextToAscii({ text, rainbow = false }: { rainbow?: boolean; text: string }) {
  const isMounted = useIsMounted();

  return (
    <>
      <span className="sr-only">{text}</span>
      <div className="min-h-[72px] animate-fade-in">{isMounted && <ASCII rainbow={rainbow} text={text} />}</div>
    </>
  );
}
