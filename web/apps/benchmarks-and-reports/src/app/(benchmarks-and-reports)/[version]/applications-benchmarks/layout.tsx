import type { Version } from "@/types/version";
import { Separator } from "@risc0/ui/separator";
import { type PropsWithChildren, type ReactNode, Suspense } from "react";
import { SuspenseLoader } from "shared/client/components/suspense-loader";
import { FooterAscii } from "../../_components/footer-ascii";
import { redirectIfWrongVersion } from "../../_utils/redirect-if-wrong-version";
import { ApplicationsBenchmarksCommitHashButton } from "./_components/applications-benchmarks-commit-hash-button";

export default async function ApplicationsBenchmarksLayout(
	props: PropsWithChildren<{
		params: Promise<{
			version: Version;
		}>;
	}>,
) {
	const params = await props.params;

	redirectIfWrongVersion(params.version);

	return (
		<div className="container max-w-screen-3xl">
			<div className="flex items-center justify-between gap-8">
				<h1 className="text-2xl">Applications Benchmarks</h1>

				<Suspense fallback={<SuspenseLoader />}>
					<ApplicationsBenchmarksCommitHashButton version={params.version} />
				</Suspense>
			</div>

			<Separator className="mt-2" />

			{props.children}

			<FooterAscii text="Applications Benchmarks" />
		</div>
	);
}
