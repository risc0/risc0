"use client";

import { default as ASCII } from "react-rainbow-ascii";

export function TextToAscii({ text, rainbow = false }: { rainbow?: boolean; text: string }) {
  return (
    <>
      <span className="sr-only">{text}</span>
      <ASCII rainbow={rainbow} text={text} />
    </>
  );
}
