import type { Version } from "@/types/version";
import { Badge } from "@risc0/ui/badge";
import { Button } from "@risc0/ui/button";
import { Popover, PopoverContent, PopoverTrigger } from "@risc0/ui/popover";
import { Separator } from "@risc0/ui/separator";
import { InfoIcon } from "lucide-react";
import Link from "next/link";
import { type PropsWithChildren, Suspense } from "react";
import { SuspenseLoader } from "shared/client/components/suspense-loader";
import { FooterAscii } from "../../_components/footer-ascii";
import { redirectIfWrongVersion } from "../../_utils/redirect-if-wrong-version";
import { DatasheetCommitHashButton } from "./_components/datasheet-commit-hash-button";

function CodeBadge({ children }: PropsWithChildren) {
  return (
    <Badge
      variant="secondary"
      className="bg-neutral-100 p-0 font-mono text-[10px] text-purple-900 leading-tight dark:bg-neutral-700 dark:text-purple-50"
    >
      {children}
    </Badge>
  );
}

export default async function DatasheetLayout(
  props: PropsWithChildren<{
    params: Promise<{
      version: Version;
    }>;
  }>,
) {
  const params = await props.params;
  const { children } = props;

  redirectIfWrongVersion(params.version);

  return (
    <div className="container max-w-screen-3xl">
      <div className="flex items-center justify-between gap-8">
        <div>
          <h1 className="text-2xl">Datasheet</h1>
          <p className="text-muted-foreground text-sm">
            The data on this page can be used to estimate the total time and work required for proving zkVM
            applications. We recommend reading about our{" "}
            <Link
              rel="noopener noreferrer"
              href="https://dev.risczero.com/api/recursion"
              target="_blank"
              className="link"
            >
              recursive proving architecture
            </Link>{" "}
            as a companion for this page.
          </p>
          <div className="text-muted-foreground text-sm">
            <Popover>
              <PopoverTrigger asChild>
                <Button variant="outline" className="my-2" startIcon={<InfoIcon />}>
                  Show Example
                </Button>
              </PopoverTrigger>
              <PopoverContent className="w-full max-w-screen-sm text-sm">
                <p>To prove 6 million cycles (6 segments), the work required is:</p>
                <br />
                <ul>
                  <li>
                    * 6 million cycles of <CodeBadge>execute</CodeBadge>
                  </li>
                  <li>
                    * 6 calls to <CodeBadge>rv32im</CodeBadge> (1M cycles)
                  </li>
                  <li>
                    * 6 calls to <CodeBadge>lift</CodeBadge>
                  </li>
                  <li>
                    * 5 calls to <CodeBadge>join</CodeBadge>
                  </li>
                  <li>
                    * 1 call to <CodeBadge>identity_p254</CodeBadge> (optional)
                  </li>
                  <li>
                    * 1 call to <CodeBadge>stark2snark</CodeBadge> (optional)
                  </li>
                </ul>
                <br />
                <p>
                  The last two steps are only required if you'd like to verify your proofs on-chain. The row labelled{" "}
                  <CodeBadge>succinct</CodeBadge> shows the cost for <CodeBadge>execute</CodeBadge> +{" "}
                  <CodeBadge>rv32im</CodeBadge> + <CodeBadge>lift</CodeBadge>. The row labelled{" "}
                  <CodeBadge>groth16</CodeBadge> shows the cost for <CodeBadge>execute</CodeBadge> +{" "}
                  <CodeBadge>rv32im</CodeBadge> + <CodeBadge>lift</CodeBadge> + <CodeBadge>identity_p254</CodeBadge> +
                  <CodeBadge>stark2snark</CodeBadge>.
                  <br />
                  <br />
                  On Bonsai, calls to <CodeBadge>rv32im</CodeBadge>, <CodeBadge>lift</CodeBadge>, and{" "}
                  <CodeBadge>join</CodeBadge> are parallellized.
                </p>
              </PopoverContent>
            </Popover>
          </div>
        </div>

        <Suspense fallback={<SuspenseLoader />}>
          <DatasheetCommitHashButton version={params.version} />
        </Suspense>
      </div>

      <Separator className="mt-2" />

      {children}

      <FooterAscii text="Datasheet" />
    </div>
  );
}
