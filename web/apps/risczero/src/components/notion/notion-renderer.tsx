"use client";

import "../../styles/notion.css";

import type { ComponentPropsWithoutRef } from "react";
import { NotionRenderer as Renderer } from "react-notion-x";

function mapPageUrl(id: string) {
  return `https://www.notion.so/${id.replaceAll("-", "")}`;
}

/**
 * Stripped down version of notion renderer.
 */
export function NotionRenderer(props: Omit<ComponentPropsWithoutRef<typeof Renderer>, "components" | "mapPageUrl">) {
  return <Renderer mapPageUrl={mapPageUrl} {...props} />;
}
