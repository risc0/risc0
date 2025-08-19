import { Badge, type BadgeProps } from "@risc0/ui/badge";
import { cn } from "@risc0/ui/cn";

type TagItemProps = BadgeProps & {
  tag: string;
};

export function TagItem({ tag, className, ...rest }: TagItemProps) {
  return (
    <Badge variant="outline" className={cn("whitespace-nowrap", className)} {...rest}>
      {tag}
    </Badge>
  );
}
