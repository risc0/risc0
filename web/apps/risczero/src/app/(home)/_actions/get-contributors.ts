"use server";

import ky from "ky";
import { actionError, createAction } from "next-extra/action";

type Contributor = {
  login: string;
  id: number;
  node_id: string;
  avatar_url: string;
  gravatar_id: string;
  url: string;
  html_url: string;
  followers_url: string;
  following_url: string;
  gists_url: string;
  starred_url: string;
  subscriptions_url: string;
  organizations_url: string;
  repos_url: string;
  events_url: string;
  received_events_url: string;
  type: string;
  site_admin: boolean;
  contributions: number;
};

export const getContributors = createAction(async () => {
  const response = await ky.get("https://api.github.com/repos/risc0/risc0/contributors", {
    throwHttpErrors: false,
    next: {
      tags: ["get-contributors"],
    },
  });

  if (response.status !== 200) {
    throw actionError("GET_CONTRIBUTORS_ERROR", "Failed to get contributors");
  }

  return response.json<Contributor[]>();
});
