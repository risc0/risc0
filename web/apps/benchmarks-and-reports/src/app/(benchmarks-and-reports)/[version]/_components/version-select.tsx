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

const VERSIONS = ["main", "0.21"];

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
      <SelectTrigger size="sm" className="capitalize">
        <SelectValue />
      </SelectTrigger>
      <SelectContent>
        <SelectGroup>
          <SelectLabel>Versions</SelectLabel>
          {VERSIONS.map((version) => (
            <SelectItem key={version} className="font-mono cursor-pointer" value={version}>
              {version}
            </SelectItem>
          ))}
        </SelectGroup>
      </SelectContent>
    </Select>
  ) : null;
}
