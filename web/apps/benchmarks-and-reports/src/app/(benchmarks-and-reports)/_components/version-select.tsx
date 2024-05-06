"use client";

import { useLocalStorage } from "@risc0/ui/hooks/use-local-storage";
import { useMounted } from "@risc0/ui/hooks/use-mounted";
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
import { useEffect } from "react";
import { VERSIONS } from "~/versions";

export function VersionSelect() {
  const { version } = useParams();
  const router = useRouter();
  const pathname = usePathname();
  const mounted = useMounted();
  const pathnameParts = compact(pathname.split("/"));
  const [_versionLocalStorage, setVersionLocalStorage] = useLocalStorage<string | undefined>("version", undefined);

  // biome-ignore lint/correctness/useExhaustiveDependencies: <explanation>
  useEffect(() => {
    if (version) {
      setVersionLocalStorage(String(version));
    }
  }, []);

  function onValueChange(value) {
    const [_, ...pathnameWithoutVersion] = pathnameParts;

    setVersionLocalStorage(value);

    router.push(`/${value}/${pathnameWithoutVersion.join("/")}`);
  }

  return mounted && version ? (
    <Select onValueChange={onValueChange} value={String(version)}>
      <SelectTrigger size="sm">
        <SelectValue />
      </SelectTrigger>
      <SelectContent>
        <SelectGroup>
          <SelectLabel>Versions</SelectLabel>
          {VERSIONS.map(({ label, value }) => (
            <SelectItem key={value} className="cursor-pointer font-mono text-xs" value={value}>
              {label}
            </SelectItem>
          ))}
        </SelectGroup>
      </SelectContent>
    </Select>
  ) : null;
}
