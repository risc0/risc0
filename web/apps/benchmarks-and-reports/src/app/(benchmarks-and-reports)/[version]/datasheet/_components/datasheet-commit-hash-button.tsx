import { truncate } from "@risc0/ui/utils/truncate";
import { CopyButton } from "shared/client/components/copy-button";
import type { Version } from "~/types/version";
import { fetchDatasheetCommitHash } from "../_actions/fetch-datasheet-commit-hash";

export async function DatasheetCommitHashButton({ version }: { version: Version }) {
  const commitHash = await fetchDatasheetCommitHash({ version });

  return (
    <CopyButton size="sm" variant="ghost" value={commitHash}>
      Commit Hash<span className="hidden sm:inline">: {truncate(commitHash, 15)}</span>
    </CopyButton>
  );
}
