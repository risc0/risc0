import type { ExtendedRecordMap } from "notion-types";
import { idToUuid } from "notion-utils";

export function getAllPageIds(collectionQuery: ExtendedRecordMap["collection_query"], viewId?: string): string[] {
  if (!collectionQuery || typeof collectionQuery !== "object") {
    return [];
  }

  const views = Object.values(collectionQuery)[0];

  if (viewId) {
    const vId = idToUuid(viewId);

    return views![vId]!.blockIds;
  }

  if (!views) {
    return [];
  }

  const pageSet = Object.values(views).reduce((set, view) => {
    // biome-ignore lint/suspicious/useIterableCallbackReturn: ignore
    view.collection_group_results?.blockIds.forEach((id) => set.add(id));

    return set;
  }, new Set<string>());

  return [...pageSet];
}
