import { Slot } from "@radix-ui/react-slot";
import cn from "@web/shared/cn";
import { type VariantProps, cva } from "class-variance-authority";
import { Loader2Icon } from "lucide-react";
import { type ButtonHTMLAttributes, type ReactElement, cloneElement, forwardRef } from "react";

const buttonVariants = cva(
  "inline-flex items-center justify-center whitespace-nowrap rounded-md text-sm font-medium transition-colors focus-visible:outline-none focus-visible:ring-1 focus-visible:ring-ring disabled:pointer-events-none disabled:opacity-50",
  {
    variants: {
      variant: {
        default: "bg-primary text-primary-foreground hover:bg-primary/90 hover:text-primary-foreground",
        destructive: "bg-destructive text-destructive-foreground hover:bg-destructive/90",
        outline: "border border-input bg-background hover:bg-accent hover:text-accent-foreground",
        secondary: "bg-secondary text-secondary-foreground hover:bg-secondary/80",
        ghost: "hover:bg-accent hover:text-accent-foreground",
      },
      size: {
        default: "h-9 px-4 py-2",
        sm: "h-8 rounded-md px-3 text-xs",
        lg: "h-10 rounded-md px-8 text-lg",
        icon: "size-9",
        "icon-sm": "size-8",
      },
    },
    defaultVariants: {
      variant: "default",
      size: "default",
    },
  },
);

const iconVariants = cva(undefined, {
  variants: {
    size: {
      default: "size-4",
      sm: "size-3",
      lg: "size-5",
      icon: "size-4 mr-0",
      "icon-sm": "size-3 mr-0",
    },
  },
  defaultVariants: {
    size: "default",
  },
});

interface ButtonProps extends ButtonHTMLAttributes<HTMLButtonElement>, VariantProps<typeof buttonVariants> {
  asChild?: boolean;
  isLoading?: boolean;
  startIcon?: ReactElement;
  endIcon?: ReactElement;
}

const Button = forwardRef<HTMLButtonElement, ButtonProps>(
  ({ className, startIcon, isLoading = false, variant, endIcon, size, children, asChild = false, ...rest }, ref) => {
    const Component = asChild ? Slot : "button";

    return (
      <Component className={cn(buttonVariants({ variant, size, className }))} ref={ref} {...rest}>
        <Loader2Icon
          className={cn(
            iconVariants({}),
            "animate-spin",
            !startIcon && "transition-all",
            isLoading ? "mr-2 max-w-4 opacity-100" : "mr-0 max-w-0 opacity-0",
          )}
        />
        {!isLoading &&
          startIcon &&
          cloneElement(startIcon as ReactElement, {
            className: cn("mr-2", iconVariants({ size }), startIcon.props.className),
          })}
        {children}
        {endIcon &&
          cloneElement(endIcon as ReactElement, {
            className: cn("ml-2", iconVariants({ size }), endIcon.props.className),
          })}
      </Component>
    );
  },
);

Button.displayName = "Button";

export { buttonVariants };

export default Button;
