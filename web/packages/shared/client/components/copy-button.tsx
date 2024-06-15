"use client";

import { Button, type ButtonProps } from "@risc0/ui/button";
import { cn } from "@risc0/ui/cn";
import { CopyIcon } from "lucide-react";
import { useState } from "react";
import { setClipboard } from "shared/utils/set-clipboard";

type CopyButtonProps = ButtonProps & {
  value: string;
};

export function CopyButton({ value, disabled, children, ...rest }: CopyButtonProps) {
  const [clicked, setClicked] = useState<boolean>(false);

  return (
    <Button
      startIcon={clicked ? undefined : <CopyIcon />}
      onClick={(event) => {
        setClicked(true);
        rest.onClick?.(event);
        setClipboard({ value });
        setTimeout(() => {
          setClicked(false);
        }, 2000);
      }}
      disabled={disabled ?? clicked}
      className={cn(`before:absolute before:opacity-0 before:content-["✓_Copied"]`, clicked && "before:opacity-100")}
      {...rest}
    >
      <div className={cn("opacity-100", clicked && "opacity-0")}>{children}</div>
    </Button>
  );
}
