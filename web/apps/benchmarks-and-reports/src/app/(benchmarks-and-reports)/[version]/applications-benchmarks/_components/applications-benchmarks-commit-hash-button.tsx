import type { Version } from "@/types/version";
import { truncate } from "@risc0/ui/utils/truncate";
import { CopyButton } from "shared/client/components/copy-button";
import { fetchApplicationsBenchmarksCommitHash } from "../[slug]/_actions/fetch-applications-benchmarks-commit-hash";

export async function ApplicationsBenchmarksCommitHashButton({
  version,
}: {
  version: Version;
}) {
  const commitHash = await fetchApplicationsBenchmarksCommitHash({ version });

  return (
    <CopyButton size="sm" variant="ghost" value={commitHash}>
      Commit Hash
      <span className="hidden sm:inline">: {truncate(commitHash, 15)}</span>
    </CopyButton>
  );
}
