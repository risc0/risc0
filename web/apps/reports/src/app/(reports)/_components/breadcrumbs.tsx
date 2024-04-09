"use client";

import {
  Breadcrumb,
  BreadcrumbItem,
  BreadcrumbLink,
  BreadcrumbList,
  BreadcrumbPage,
  BreadcrumbSeparator,
} from "@risc0/ui/breadcrumb";
import compact from "lodash-es/compact";
import { ChevronRightIcon } from "lucide-react";
import { usePathname } from "next/navigation";
import { Fragment } from "react";
import { replaceAll } from "string-ts";

export function Breadcrumbs() {
  const pathname = usePathname();
  const paths = compact(pathname.split("/"));

  if (pathname === "/") {
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
            <BreadcrumbLink href="/">Home</BreadcrumbLink>
          </BreadcrumbItem>
          <BreadcrumbSeparator>
            <ChevronRightIcon />
          </BreadcrumbSeparator>
          {paths.map((path, index, { length }) => {
            const isLast = length - 1 === index;
            const sanitizedChunk = replaceAll(path, "-", " ");

            return (
              <Fragment key={path}>
                {isLast ? (
                  <BreadcrumbPage className="capitalize">{sanitizedChunk}</BreadcrumbPage>
                ) : (
                  <BreadcrumbItem>
                    <BreadcrumbLink className="capitalize" href={`/${path}`}>
                      {sanitizedChunk}
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
