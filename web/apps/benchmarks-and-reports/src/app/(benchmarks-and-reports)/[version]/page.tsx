import { Card, CardDescription, CardTitle } from "@risc0/ui/card";
import Link from "next/link";
import { REPORTS } from "./_utils/constants";

export default function ReportsPage({ params }) {
  return (
    <div className="container grid max-w-screen-3xl grid-cols-1 gap-10 pt-4 lg:grid-cols-2">
      {REPORTS.map(({ label, href, description, showVersionSelect }, index) => (
        <Link prefetch key={href} href={`${showVersionSelect ? `/${params.version}` : ""}${href}`} className="group">
          <Card className="group-hover:-translate-y-1 flex h-full min-h-44 w-full flex-col items-center justify-between gap-1 border-2 border-border px-8 py-4 shadow-sm transition-transform md:flex-row md:gap-12 hover:border-primary dark:bg-neutral-900">
            <div>
              <CardTitle className="text-xl">{label}</CardTitle>
              <CardDescription className="text-sm">{description}</CardDescription>
            </div>

            <div className="flex min-h-[160px] min-w-[220px] justify-center">
              <img
                width={220}
                height={160}
                className="dark:filter-order-colored-svg-filter-order user-select-none pointer-events-none rounded object-contain object-right invert dark:brightness-100 dark:hue-rotate-[3deg] dark:invert-0 dark:saturate-[6] dark:sepia"
                src={`/graph-${index}.svg`}
                alt={description}
              />
            </div>
          </Card>
        </Link>
      ))}
    </div>
  );
}
