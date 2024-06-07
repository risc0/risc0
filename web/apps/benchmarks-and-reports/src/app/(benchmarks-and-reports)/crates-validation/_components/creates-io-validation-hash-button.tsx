import { truncate } from "@risc0/ui/utils/truncate";
import { CopyButton } from "shared/client/components/copy-button";
import { HtmlComment } from "shared/client/components/html-comment";
import { findMostRecentHash } from "../_actions/find-most-recent-hash";

export async function CratesIoValidationHashButton() {
  const { data: hash, fetchedAt } = await findMostRecentHash();

  return (
    <>
      <HtmlComment text={`Fetched at ${new Date(fetchedAt)}`} />
      <CopyButton size="sm" variant="ghost" value={hash}>
        Commit Hash<span className="hidden sm:inline">: {truncate(hash, 15)}</span>
      </CopyButton>
    </>
  );
}
