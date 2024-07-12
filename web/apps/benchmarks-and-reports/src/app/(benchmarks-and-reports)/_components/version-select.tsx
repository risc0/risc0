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
import { useParams, usePathname, useRouter } from "next/navigation";
import { startTransition, useEffect } from "react";
import { useProgressBar } from "shared/client/providers/progress-bar-provider";
import type { Version } from "~/types/version";
import { VERSIONS } from "~/versions";

export function VersionSelect() {
  const { version } = useParams<{ version: Version }>();
  const router = useRouter();
  const pathname = usePathname();
  const mounted = useMounted();
  const progress = useProgressBar();
  const pathnameParts = pathname.split("/").filter(Boolean);
  const [_versionLocalStorage, setVersionLocalStorage] = useLocalStorage<string | undefined>("version", undefined);

  // biome-ignore lint/correctness/useExhaustiveDependencies: <explanation>
  useEffect(() => {
    if (version) {
      setVersionLocalStorage(version);
    }
  }, []);

  function onValueChange(value) {
    const [_, ...pathnameWithoutVersion] = pathnameParts;

    setVersionLocalStorage(value);

    progress.start();

    startTransition(() => {
      router.push(`/${value}/${pathnameWithoutVersion.join("/")}`);
      progress.done();
    });
  }

  return mounted && version ? (
    <Select onValueChange={onValueChange} value={version}>
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
