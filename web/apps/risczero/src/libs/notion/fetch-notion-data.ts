import { idToUuid } from "notion-utils";
import type { Investor, Leadership, Post, Project } from "@/app/blog/_types";
import { getPage } from "./api";
import { filterPublished } from "./filter-published";
import { getAllPageIds } from "./get-all-page-ids";
import { getPageCovers } from "./get-page-covers";
import { getPageProperties } from "./get-page-properties";

export async function fetchNotionData<T extends Leadership | Investor | Project | Post>(databaseId: string) {
  const id = idToUuid(databaseId);
  const response = await getPage(id);

  if (!response?.collection || typeof response.collection !== "object") {
    return null;
  }

  const collection = Object.values(response.collection)[0]?.value;

  if (!collection) {
    return null;
  }

  const { block } = response;
  const collectionQuery = response.collection_query;
  const { schema } = collection;
  const rawMetadata = block[id]?.value;

  if (rawMetadata?.type !== "collection_view_page" && rawMetadata?.type !== "collection_view") {
    throw new Error(`pageId "${id}" is not a database`);
  }

  const pageIds = getAllPageIds(collectionQuery);
  const pageCoverMap = getPageCovers(block);
  const propertiesArray = pageIds.map((pageId) => getPageProperties(pageId, block, schema));

  const items: T[] = pageIds.map((pageId, index) => {
    const properties = propertiesArray[index];
    const pageCover = pageCoverMap[pageId] ?? "";

    if (properties && "tags" in properties && properties.tags) {
      const tags = properties.tags.map((tag) => ({ tag }));
      return { ...properties, pageCover, tags } as T;
    }

    return { ...properties, pageCover } as T;
  });

  const filteredItems = filterPublished<T>({ entries: items });

  return filteredItems;
}
