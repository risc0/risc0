"use client";

import * as TooltipPrimitive from "@radix-ui/react-tooltip";
import cn from "@web/shared/cn";
import { type ComponentPropsWithoutRef, type ElementRef, forwardRef } from "react";

const TooltipContent = forwardRef<
  ElementRef<typeof TooltipPrimitive.Content>,
  ComponentPropsWithoutRef<typeof TooltipPrimitive.Content> & {
    // any other prop goes here
    isInfo?: boolean;
  }
>(({ className, sideOffset = 4, isInfo = false, ...rest }, ref) => (
  <TooltipPrimitive.Content
    ref={ref}
    sideOffset={sideOffset}
    className={cn(
      "fade-in-0 zoom-in-95 data-[state=closed]:fade-out-0 data-[state=closed]:zoom-out-95 data-[side=bottom]:slide-in-from-top-2 data-[side=left]:slide-in-from-right-2 data-[side=right]:slide-in-from-left-2 data-[side=top]:slide-in-from-bottom-2 z-50 animate-in overflow-hidden rounded-md bg-primary px-3 py-1.5 text-primary-foreground text-xs data-[state=closed]:animate-out",
      isInfo && "cursor-help",
      className,
    )}
    {...rest}
  />
));

TooltipContent.displayName = TooltipPrimitive.Content.displayName;

const TooltipProvider = TooltipPrimitive.Provider;
const Tooltip = TooltipPrimitive.Root;
const TooltipTrigger = TooltipPrimitive.Trigger;

export { Tooltip, TooltipTrigger, TooltipContent, TooltipProvider };
