"use client";

import type { Version } from "@/types/version";
import { VERSIONS } from "@/versions";
import { useIsMounted } from "@risc0/ui/hooks/use-is-mounted";
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
import { useVersion } from "../_hooks/use-version";

export function VersionSelect() {
	const { version } = useParams<{ version: Version }>();
	const router = useRouter();
	const pathname = usePathname();
	const isMounted = useIsMounted();
	const progress = useProgressBar();
	const pathnameParts = pathname.split("/").filter(Boolean);
	const { setVersion: setVersionLocalStorage } = useVersion();

	// biome-ignore lint/correctness/useExhaustiveDependencies: <explanation>
	useEffect(() => {
		if (version) {
			setVersionLocalStorage(version);
		}
	}, []);

	function onValueChange(value: Version) {
		const [_, ...pathnameWithoutVersion] = pathnameParts;

		setVersionLocalStorage(value);

		progress.start();

		startTransition(() => {
			router.push(`/${value}/${pathnameWithoutVersion.join("/")}`);
			progress.done();
		});
	}

	return isMounted && version ? (
		<Select onValueChange={onValueChange} value={version}>
			<SelectTrigger size="sm" aria-label="version select">
				<SelectValue />
			</SelectTrigger>
			<SelectContent>
				<SelectGroup>
					<SelectLabel>Versions</SelectLabel>
					{VERSIONS.map(({ label, value }) => (
						<SelectItem
							key={value}
							className="cursor-pointer font-mono text-xs"
							value={value}
						>
							{label}
						</SelectItem>
					))}
				</SelectGroup>
			</SelectContent>
		</Select>
	) : null;
}
