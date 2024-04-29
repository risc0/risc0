"use client";

import { Button, type ButtonProps } from "@risc0/ui/button";
import { setClipboard } from "@risc0/ui/utils/set-clipboard";
import { CopyIcon } from "lucide-react";

type CopyButtonProps = ButtonProps & {
  value: string;
};

export function CopyButton({ value, children, ...rest }: CopyButtonProps) {
  return (
    <Button
      startIcon={<CopyIcon />}
      onClick={(event) => {
        rest.onClick?.(event);
        setClipboard({ value });
      }}
      {...rest}
    >
      {children}
    </Button>
  );
}
