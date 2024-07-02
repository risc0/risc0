import { redirect } from "next/navigation";
import type { Version } from "~/types/version";
import { getFirstApplicationBenchmark } from "./_utils/get-first-application-benchmark";

export default function ApplicationsBenchmarksPage({
  params,
}: {
  params: {
    version: Version;
  };
}) {
  // redirect to the first application benchmark
  redirect(`/${params.version}/applications-benchmarks/${getFirstApplicationBenchmark(params.version)}`);
}
