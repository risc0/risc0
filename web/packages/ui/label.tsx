"use client";

import * as LabelPrimitive from "@radix-ui/react-label";
import cn from "@web/shared/cn";
import type { VariantProps } from "class-variance-authority";
import { type ComponentPropsWithoutRef, type ElementRef, forwardRef } from "react";
import { tv } from "tailwind-variants";

const labelVariants = tv({
  base: "text-sm font-medium leading-none peer-disabled:cursor-not-allowed peer-disabled:opacity-70",
});

const Label = forwardRef<
  ElementRef<typeof LabelPrimitive.Root>,
  ComponentPropsWithoutRef<typeof LabelPrimitive.Root> & VariantProps<typeof labelVariants>
>(({ className, ...rest }, ref) => (
  <LabelPrimitive.Root ref={ref} className={cn(labelVariants(), className)} {...rest} />
));

Label.displayName = LabelPrimitive.Root.displayName;

export default Label;
