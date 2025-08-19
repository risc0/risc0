import type { BlockMap } from "notion-types";

const BASE_URL = "https://www.notion.so";

export function getPageCovers(block: BlockMap): Record<string, string> {
  if (!block || typeof block !== "object") {
    return {};
  }

  const pageCovers = Object.values(block)
    .filter(({ value }) => value.type === "page")
    .map(({ value }) => ({
      id: value.id,
      page_cover: value.format?.page_cover,
    }));

  return pageCovers.reduce<Record<string, string>>((pageCoverMap, { id, page_cover }) => {
    if (!page_cover) {
      pageCoverMap[id] = "";

      return pageCoverMap;
    }

    const targetURL = new URL(BASE_URL);

    try {
      const url = new URL(page_cover);

      targetURL.pathname = `/image/${encodeURIComponent(url.toString())}`;
      targetURL.searchParams.set("table", "block");
      targetURL.searchParams.set("cache", "v2");
      targetURL.searchParams.set("id", id);
    } catch {
      targetURL.pathname = page_cover;
    } finally {
      pageCoverMap[id] = targetURL.toString();
    }

    return pageCoverMap;
  }, {});
}
