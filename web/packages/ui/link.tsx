"use client";

import cn from "@web/shared/cn";
import { addBasePath } from "next/dist/client/add-base-path";
import NextLink from "next/link";
import NProgress from "nprogress";
import { type ComponentProps, type MouseEvent, forwardRef } from "react";

function onStart() {
  NProgress.start();
}

function getURL(href: string): URL {
  return new URL(addBasePath(href), location.href);
}

// https://github.com/vercel/next.js/blob/400ccf7b1c802c94127d8d8e0d5e9bdf9aab270c/packages/next/src/client/link.tsx#L169
function isModifiedEvent(event: MouseEvent): boolean {
  const eventTarget = event.currentTarget as HTMLAnchorElement | SVGAElement;
  const target = eventTarget.getAttribute("target");

  return (
    (target && target !== "_self") ||
    event.metaKey ||
    event.ctrlKey ||
    event.shiftKey ||
    event.altKey || // triggers resource download
    (event.nativeEvent && event.nativeEvent.button === 1)
  );
}

function shouldTriggerStartEvent(href: string, clickEvent?: MouseEvent) {
  const current = window.location;
  const target = getURL(href);

  if (clickEvent && isModifiedEvent(clickEvent)) {
    return false; // modified events: fallback to browser behaviour
  }

  if (current.origin !== target.origin) {
    return false; // external URL
  }

  if (current.pathname === target.pathname && current.search === target.search) {
    return false; // same URL
  }

  return true;
}

// a wrapped <Link /> component that supports page transitions with loading indicator bar
// taken from https://github.com/designly1/nextjs13-progress
const Link = forwardRef<HTMLAnchorElement, ComponentProps<"a">>(function Link(
  { href, className, onClick, ...rest },
  ref,
) {
  const useNextJsLink = href?.startsWith("/");

  if (!useNextJsLink) {
    return <a href={href} onClick={onClick} {...rest} />;
  }

  return (
    href && (
      <NextLink
        href={href}
        className={cn("cursor-pointer underline-offset-4 transition-colors hover:text-primary", className)}
        onClick={(event) => {
          if (shouldTriggerStartEvent(href, event)) {
            onStart();
          }

          if (onClick) {
            onClick(event);
          }
        }}
        {...rest}
        ref={ref}
      />
    )
  );
});

export default Link;
