"use client";

import {
  Select,
  SelectContent,
  SelectGroup,
  SelectItem,
  SelectLabel,
  SelectTrigger,
  SelectValue,
} from "@risc0/ui/select";
import compact from "lodash-es/compact";
import { useParams, usePathname, useRouter } from "next/navigation";
import { useEffect, useState } from "react";

const VERSIONS = [
  { label: "next", value: "main" },
  { label: "release-0.21", value: "0.21" },
];

export function VersionSelect() {
  const { version } = useParams();
  const router = useRouter();
  const pathname = usePathname();
  const [mounted, setMounted] = useState<boolean>(false);
  const pathnameParts = compact(pathname.split("/"));

  useEffect(() => {
    setMounted(true);
  }, []);

  return mounted ? (
    <Select
      onValueChange={(value) => {
        const [_, ...pathnameWithoutVersion] = pathnameParts;

        router.push(`/${value}/${pathnameWithoutVersion.join("/")}`);
      }}
      value={String(version)}
    >
      <SelectTrigger size="sm">
        <SelectValue />
      </SelectTrigger>
      <SelectContent>
        <SelectGroup>
          <SelectLabel>Versions</SelectLabel>
          {VERSIONS.map(({ label, value }) => (
            <SelectItem key={value} className="font-mono cursor-pointer" value={value}>
              {label}
            </SelectItem>
          ))}
        </SelectGroup>
      </SelectContent>
    </Select>
  ) : null;
}
