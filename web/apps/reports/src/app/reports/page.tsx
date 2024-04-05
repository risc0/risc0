import { Card, CardDescription, CardTitle } from "@risc0/ui/card";
import { Link } from "@risc0/ui/link";
import Image from "next/image";

const REPORTS = [
  {
    label: "Crates.io Validation",
    href: "/reports/crates-io-validation",
    description: "View the latest Crates.io validation results",
  },
  {
    label: "Benchmarks",
    href: "/reports/benchmarks",
    description: "View the latest benchmarks for the RISC Zero platform",
  },
  {
    label: "Applications Benchmarks",
    href: "/reports/applications-benchmarks",
    description: "View the latest applications benchmarks for the RISC Zero platform",
  },
  {
    label: "Datasheet",
    href: "/reports/datasheet",
    description: "View the latest datasheet for the RISC Zero platform",
  },
] as const;

export default function ReportsPage() {
  return (
    <div className="container grid max-w-screen-xl grid-cols-1 gap-4 pt-4 lg:grid-cols-2">
      {REPORTS.map(({ label, href, description }, index) => (
        <Link href={href} className="group transition-opacity hover:opacity-70">
          <Card className="group-hover:-translate-y-1 flex h-full min-h-44 w-full flex-col gap-1 md:flex-row items-center justify-between md:gap-12 px-8 py-4 shadow-sm transition-transform">
            <div>
              <CardTitle className="text-xl">{label}</CardTitle>
              <CardDescription className="text-xs">{description}</CardDescription>
            </div>
            <div className="flex min-h-[160px] min-w-[220px] justify-center">
              <Image
                width={220}
                height={160}
                priority
                className="user-select-none pointer-events-none hidden rounded object-contain object-right dark:block"
                src={`/graph-${index}-dark.svg`}
                alt={description}
                quality={100}
              />
              <Image
                width={220}
                height={160}
                priority
                className={"user-select-none pointer-events-none rounded object-contain object-right dark:hidden"}
                src={`/graph-${index}.svg`}
                alt={description}
                quality={100}
              />
            </div>
          </Card>
        </Link>
      ))}
    </div>
  );
}
