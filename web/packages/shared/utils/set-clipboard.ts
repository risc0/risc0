import { toast } from "sonner";

export const setClipboard = ({
  value,
  onSuccess = () => toast.success("Copied to clipboard"),
  onFailure = () => toast.error("Failed to copy to clipboard"),
}: {
  onFailure?: () => void;
  onSuccess?: () => void;
  value: string;
}) => {
  navigator.clipboard
    .writeText(value)
    .then(() => {
      onSuccess?.();
    })
    .catch(() => {
      onFailure?.();
    });
};
