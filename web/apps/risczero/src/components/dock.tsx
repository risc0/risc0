"use client";

import { cn } from "@risc0/ui/cn";
import { type VariantProps, cva } from "class-variance-authority";
import { type MotionValue, motion, useMotionValue, useSpring, useTransform } from "motion/react";
import {
  Children,
  type PropsWithChildren,
  type ReactNode,
  cloneElement,
  forwardRef,
  isValidElement,
  useRef,
} from "react";

interface DockChildProps {
  mouseX: MotionValue<number>;
  magnification: number;
  distance: number;
}

interface DockProps extends VariantProps<typeof dockVariants> {
  className?: string;
  magnification?: number;
  label?: ReactNode;
  distance?: number;
  direction?: "top" | "middle" | "bottom";
}

const DEFAULT_MAGNIFICATION = 60;
const DEFAULT_DISTANCE = 140;

const dockVariants = cva(
  "flex h-[48px] w-max gap-2 rounded-2xl backdrop-blur-md supports-backdrop-blur:bg-white/10 supports-backdrop-blur:dark:bg-black/10",
);

const Dock = forwardRef<HTMLDivElement, PropsWithChildren<DockProps>>(
  (
    {
      className,
      children,
      label,
      magnification = DEFAULT_MAGNIFICATION,
      distance = DEFAULT_DISTANCE,
      direction = "bottom",
      ...props
    },
    ref,
  ) => {
    const mouseX = useMotionValue(Number.POSITIVE_INFINITY);

    function renderChildren() {
      return Children.map(children, (child) => {
        if (isValidElement<DockChildProps>(child)) {
          return cloneElement(child, {
            mouseX,
            magnification,
            distance,
          });
        }
        return child;
      });
    }

    return (
      <motion.div
        ref={ref}
        onMouseMove={(e) => {
          mouseX.set(e.pageX);
        }}
        onMouseLeave={() => {
          mouseX.set(Number.POSITIVE_INFINITY);
        }}
        {...props}
        className={cn(dockVariants({ className }), {
          "items-start": direction === "top",
          "items-center": direction === "middle",
          "items-end": direction === "bottom",
        })}
      >
        {label && <span className="pr-4 text-muted-foreground">{label}</span>}

        {renderChildren()}
      </motion.div>
    );
  },
);

type DockIconProps = {
  magnification?: number;
  distance?: number;
  mouseX?: any;
  className?: string;
  props?: PropsWithChildren;
};

function DockIcon({
  magnification = DEFAULT_MAGNIFICATION,
  distance = DEFAULT_DISTANCE,
  mouseX,
  className,
  children,
  ...props
}: PropsWithChildren<DockIconProps>) {
  const ref = useRef<HTMLDivElement>(null);

  const distanceCalc = useTransform(mouseX, (val: number) => {
    const bounds = ref.current?.getBoundingClientRect() ?? { x: 0, width: 0 };

    return val - bounds.x - bounds.width / 2;
  });

  const widthSync = useTransform(distanceCalc, [-distance, 0, distance], [40, magnification, 40]);

  const width = useSpring(widthSync, {
    mass: 0.1,
    stiffness: 150,
    damping: 12,
  });

  return (
    <motion.div
      ref={ref}
      style={{ width }}
      className={cn("flex aspect-square cursor-pointer items-center justify-center rounded-full", className)}
      {...props}
    >
      {children}
    </motion.div>
  );
}

DockIcon.displayName = "DockIcon";
Dock.displayName = "Dock";

export { Dock, DockIcon };
