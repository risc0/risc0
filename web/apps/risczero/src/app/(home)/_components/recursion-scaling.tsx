"use client";

import { Card, CardContent, CardDescription, CardHeader } from "@risc0/ui/card";
import { type ChartConfig, ChartContainer, ChartLegend, ChartLegendContent } from "@risc0/ui/chart";
import { useTheme } from "next-themes";
import { useEffect } from "react";
import { Bar, BarChart, XAxis } from "recharts";
import { Subtitle } from "@/app/_components/subtitle";
import { isAtTop } from "@/utils/is-at-top";

const chartData = [
  { batchSize: "2", risc: 262144, other: 406552 },
  { batchSize: "5", risc: 524288, other: 1029005 },
  { batchSize: "10", risc: 1048576, other: 2101183 },
  { batchSize: "20", risc: 1572864, other: 4314087 },
];

const chartConfig = {
  risc: {
    label: "RISC Zero",
    theme: {
      light: "hsl(61 100% 80.8%)",
      dark: "hsl(var(--primary))",
    },
  },
  other: {
    label: "Other",
    theme: {
      light: "hsl(var(--muted-foreground))",
      dark: "hsl(var(--muted-foreground))",
    },
  },
} as const satisfies ChartConfig;

export function RecursionScaling() {
  const { resolvedTheme } = useTheme();
  const isDark = resolvedTheme === "dark";

  useEffect(() => {
    const recursionScalingDiv = document.querySelector("#graph-recursion-scaling");

    function handleScroll() {
      if (isAtTop(recursionScalingDiv)) {
        recursionScalingDiv?.classList.add("md:opacity-100", "md:pointer-events-auto");
      } else {
        recursionScalingDiv?.classList.remove("md:opacity-100", "md:pointer-events-auto");
      }
    }

    window.addEventListener("scroll", handleScroll);

    handleScroll(); // initial load

    return () => {
      window.removeEventListener("scroll", handleScroll);
    };
  }, []);

  return (
    <Card className="w-full animate-fade-in-left border-none bg-transparent">
      <CardHeader className="-mb-4 items-center p-0 text-center">
        <Subtitle className="max-w-none font-normal md:text-lg" as="h4">
          Efficient Cycle Usage for Aggregation
        </Subtitle>

        <CardDescription className="text-center text-muted-foreground text-sm italic">
          Lower is better — Examples include L1s, Rollups, and AVSs
        </CardDescription>
      </CardHeader>
      <CardContent className="p-0">
        <ChartContainer config={chartConfig}>
          <BarChart accessibilityLayer data={chartData}>
            <XAxis
              dataKey="batchSize"
              tickLine={false}
              tickMargin={5}
              axisLine={false}
              tickFormatter={(value) => `Batch Size of ${value}`}
            />

            <ChartLegend content={<ChartLegendContent />} />

            <Bar
              dataKey="risc"
              fill="var(--color-risc)"
              radius={10}
              strokeWidth={isDark ? 0 : 2}
              stroke="hsl(var(--muted-foreground))"
            />

            <Bar dataKey="other" fill="var(--color-other)" radius={10} />
          </BarChart>
        </ChartContainer>
      </CardContent>
    </Card>
  );
}
