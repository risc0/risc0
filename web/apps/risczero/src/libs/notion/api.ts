import "server-only";

import { unstable_cache } from "next/cache";
import { NotionAPI } from "notion-client";
import type { ExtendedRecordMap, RecordValues, User } from "notion-types";
import env from "@/env";

const client = new NotionAPI({
  authToken: env.NOTION_TOKEN,
  activeUser: env.NOTION_ACTIVE_USER,
});

let cachedPage: ExtendedRecordMap | null = null;

export function getUsers(ids: string[]) {
  return unstable_cache(
    async (): Promise<RecordValues<User>> => {
      try {
        const users = await client.getUsers(ids);

        if (!users) {
          throw new Error("No users returned");
        }

        return users;
      } catch (error) {
        console.error("Error fetching users:", error);
        throw error; // Re-throw the error to be handled by the caller
      }
    },
    [`get-users-${ids.join("-")}`],
    {
      tags: [`get-users-${ids.join("-")}`],
    },
  )();
}

export function getPage(id: string) {
  return unstable_cache(
    async (): Promise<ExtendedRecordMap | null> => {
      try {
        const page = await client.getPage(id);

        if (!page) {
          console.warn("No page returned, using cached page if available");
          return cachedPage;
        }

        cachedPage = page;

        return page;
      } catch (error) {
        console.error("Error fetching page:", error);
        console.warn("Using cached page due to error");
        return cachedPage;
      }
    },
    [`get-page-${id}`],
    {
      tags: [`get-page-${id}`],
    },
  )();
}
