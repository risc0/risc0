"use client";

import { Button, type ButtonProps } from "@risc0/ui/button";
import { CopyIcon } from "lucide-react";
import { setClipboard } from "shared/utils/set-clipboard";

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
