import type { Version } from "@/types/version";
import { redirect } from "next/navigation";
import { getFirstApplicationBenchmark } from "./_utils/get-first-application-benchmark";

export default async function ApplicationsBenchmarksPage(props: {
	params: Promise<{
		version: Version;
	}>;
}) {
	const params = await props.params;

	// redirect to the first application benchmark
	redirect(
		`/${params.version}/applications-benchmarks/${getFirstApplicationBenchmark(params.version)}`,
	);
}
