"use client";

import type { Version } from "@/types/version";
import {
  Breadcrumb,
  BreadcrumbItem,
  BreadcrumbLink,
  BreadcrumbList,
  BreadcrumbPage,
  BreadcrumbSeparator,
} from "@risc0/ui/breadcrumb";
import { useIsMounted } from "@risc0/ui/hooks/use-is-mounted";
import { joinWords } from "@risc0/ui/utils/join-words";
import { ChevronRightIcon } from "lucide-react";
import Link from "next/link";
import { useParams, usePathname } from "next/navigation";
import { Fragment } from "react";
import { useVersion } from "../_hooks/use-version";

// Routes you don't want to show up in the breadcrumb
const HIDDEN_BREADCRUMB_ROUTES = ["applications-benchmarks", "benchmarks"];

export function Breadcrumbs() {
  const pathname = usePathname();
  const { version } = useParams<{ version: Version }>();
  const paths = pathname.split("/").filter(Boolean);
  const isMounted = useIsMounted();
  const { version: versionLocalStorage } = useVersion();

  if (version) {
    paths.shift(); // remove version number from URL
  }

  if (pathname === "/" || paths.length === 0) {
    // non-breaking space to keep alignment
    return <>&nbsp;</>;
  }

  return (
    <>
      {/* non-breaking space to keep alignment */}
      <div className="block md:hidden">&nbsp;</div>

      <Breadcrumb className="hidden md:block">
        <BreadcrumbList>
          <BreadcrumbItem>
            <BreadcrumbLink asChild>
              <Link href={isMounted ? `/${version ?? versionLocalStorage ?? ""}` : "/"}>Home</Link>
            </BreadcrumbLink>
          </BreadcrumbItem>
          <BreadcrumbSeparator>
            <ChevronRightIcon />
          </BreadcrumbSeparator>
          {paths
            .filter((path) => !HIDDEN_BREADCRUMB_ROUTES.includes(path))
            .map((path, index, { length }) => {
              const isLast = length - 1 === index;
              const sanitizedChunk = joinWords(path);

              return (
                <Fragment key={path}>
                  {isLast ? (
                    <BreadcrumbPage className="capitalize">{sanitizedChunk}</BreadcrumbPage>
                  ) : (
                    <BreadcrumbItem>
                      <BreadcrumbLink asChild>
                        <Link className="capitalize" href={`/${version}/${path}`}>
                          {sanitizedChunk}
                        </Link>
                      </BreadcrumbLink>
                    </BreadcrumbItem>
                  )}
                  {length - 1 !== index && (
                    <BreadcrumbSeparator>
                      <ChevronRightIcon />
                    </BreadcrumbSeparator>
                  )}
                </Fragment>
              );
            })}
        </BreadcrumbList>
      </Breadcrumb>
    </>
  );
}
