import { toast } from "sonner";

type SetClipboardParams = {
  onFailure?: () => void;
  onSuccess?: () => void;
  value: string;
};

const setClipboard = ({
  value,
  onSuccess = () => toast.success("Copied to clipboard"),
  onFailure = () => toast.error("Failed to copy to clipboard"),
}: SetClipboardParams) => {
  navigator.clipboard
    .writeText(value)
    .then(() => {
      onSuccess?.();
    })
    .catch(() => {
      onFailure?.();
    });
};

export default setClipboard;
