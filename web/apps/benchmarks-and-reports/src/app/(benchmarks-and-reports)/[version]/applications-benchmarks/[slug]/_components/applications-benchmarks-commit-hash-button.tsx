import { truncate } from "@risc0/ui/utils/truncate";
import { CopyButton } from "shared/client/components/copy-button";
import { fetchApplicationsBenchmarksCommitHash } from "../_actions/fetch-applications-benchmarks-commit-hash";

export async function ApplicationsBenchmarksCommitHashButton({ version }) {
  const commitHash = await fetchApplicationsBenchmarksCommitHash({ version });

  if (!commitHash) {
    return null;
  }

  return (
    <CopyButton size="sm" variant="ghost" value={commitHash}>
      Commit Hash<span className="hidden sm:inline">: {truncate(commitHash, 15)}</span>
    </CopyButton>
  );
}
