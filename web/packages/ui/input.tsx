import cn from "@web/shared/cn";
import { type InputHTMLAttributes, forwardRef } from "react";

export interface InputProps extends InputHTMLAttributes<HTMLInputElement> {
  // any other prop goes here
}

const Input = forwardRef<HTMLInputElement, InputProps>(({ className, type, ...rest }, ref) => (
  <input
    type={type}
    className={cn(
      "flex h-9 w-full rounded-md border border-input bg-transparent px-3 py-1 text-sm transition-colors disabled:cursor-not-allowed file:border-0 file:bg-transparent file:font-medium file:text-sm placeholder:text-muted-foreground disabled:opacity-50 focus-visible:outline-none focus-visible:ring-1 focus-visible:ring-ring",
      className,
    )}
    ref={ref}
    {...rest}
  />
));

Input.displayName = "Input";

export default Input;
