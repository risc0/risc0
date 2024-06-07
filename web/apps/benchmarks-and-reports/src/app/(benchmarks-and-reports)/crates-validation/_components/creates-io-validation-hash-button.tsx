import { truncate } from "@risc0/ui/utils/truncate";
import { CopyButton } from "shared/client/components/copy-button";
import { RenderedTimeAgo } from "shared/client/components/rendered-time-ago";
import { findMostRecentHash } from "../_actions/find-most-recent-hash";

export async function CratesIoValidationHashButton() {
  const hash = await findMostRecentHash();

  return (
    <>
      <RenderedTimeAgo timestamp={Date.now()} />
      <CopyButton size="sm" variant="ghost" value={hash}>
        Commit Hash<span className="hidden sm:inline">: {truncate(hash, 15)}</span>
      </CopyButton>
    </>
  );
}
