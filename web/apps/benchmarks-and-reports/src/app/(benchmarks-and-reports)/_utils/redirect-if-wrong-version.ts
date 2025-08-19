import type { Version } from "@/types/version";
import { VERSIONS } from "@/versions";
import { redirect } from "next/navigation";

export function redirectIfWrongVersion(version: Version) {
	if (VERSIONS.findIndex(({ value }) => value === version) === -1) {
		redirect("/");
	}
}
