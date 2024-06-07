import { truncate } from "@risc0/ui/utils/truncate";
import { CopyButton } from "shared/client/components/copy-button";
import { HtmlComment } from "shared/client/components/html-comment";
import type { Version } from "~/types/version";
import { fetchApplicationsBenchmarksCommitHash } from "../[slug]/_actions/fetch-applications-benchmarks-commit-hash";

export async function ApplicationsBenchmarksCommitHashButton({
  version,
}: {
  version: Version;
}) {
  const { data: commitHash, fetchedAt } = await fetchApplicationsBenchmarksCommitHash({ version });

  return (
    <>
      <HtmlComment text={`Fetched at ${new Date(fetchedAt)}`} />
      <CopyButton size="sm" variant="ghost" value={commitHash}>
        Commit Hash<span className="hidden sm:inline">: {truncate(commitHash, 15)}</span>
      </CopyButton>
    </>
  );
}
