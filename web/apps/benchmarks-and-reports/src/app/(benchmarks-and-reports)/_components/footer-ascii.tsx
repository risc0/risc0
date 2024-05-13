import { TextToAscii } from "shared/client/components/text-to-ascii";

export function FooterAscii({ text }: { text: string }) {
  return (
    <div className="mt-12 flex items-center justify-center overflow-hidden text-muted-foreground [&_pre:last-child]:hidden [&_pre]:text-center dark:text-primary">
      <TextToAscii text={text} />
    </div>
  );
}
