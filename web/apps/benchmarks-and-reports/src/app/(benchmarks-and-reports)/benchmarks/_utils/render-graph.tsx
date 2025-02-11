import { Badge } from "@risc0/ui/badge";
import { Card, CardContent, CardHeader, CardTitle } from "@risc0/ui/card";
import { type ChartConfig, ChartContainer, ChartTooltip } from "@risc0/ui/chart";
import { joinWords } from "@risc0/ui/utils/join-words";
import { Area, AreaChart, CartesianGrid, Label, XAxis, YAxis } from "recharts";
import { formatNumber } from "shared/utils/format-number";
import type { FormattedDataSetEntry } from "./collect-benches-per-test-case";

function CustomTooltip({ active, payload }) {
  if (active && payload && payload.length) {
    const data = payload[0].payload;

    return (
      <div className="w-[480px] rounded-md bg-black p-2 text-white shadow-2xl">
        <strong className="mb-4 flex w-full items-center justify-between truncate font-mono text-sm">
          <span>
            {data.value} {data.unit}
          </span>
          <span className="ml-4 text-[10px] text-muted-foreground">({formatNumber(data.rawValue)} Hz)</span>
        </strong>
        <div>
          Commit{" "}
          <Badge className="rounded-[4px] px-0.5 py-0" variant="secondary">
            {data.commit}
          </Badge>
        </div>
        <br />
        <div className="line-clamp-4">{data.commitMessage}</div>
        <br />
        <div className="text-[11px]">
          {`Committed on ${new Date(data.commitTimestamp).toUTCString()} by`}{" "}
          <Badge className="rounded-[4px] px-0.5 py-0" variant="secondary">
            @{data.committer}
          </Badge>
        </div>
      </div>
    );
  }

  return null;
}

function roundToNiceNumber(value: number) {
  const magnitude = 10 ** Math.floor(Math.log10(value));
  const normalized = value / magnitude;

  if (normalized <= 1) {
    return Math.ceil(value);
  }

  if (normalized <= 2) {
    return Math.ceil(value / 2) * 2;
  }

  if (normalized <= 5) {
    return Math.ceil(value / 5) * 5;
  }

  return Math.ceil(value / 10) * 10;
}

function determineUnit(values: number[]): "MHz" | "kHz" | "Hz" {
  const maxValue = Math.max(...values);

  if (maxValue >= 1_000_000) {
    return "MHz";
  }

  if (maxValue >= 1_000) {
    return "kHz";
  }

  return "Hz";
}

function convertToUnit(hz: number, unit: "MHz" | "kHz" | "Hz"): number {
  switch (unit) {
    case "MHz":
      return hz / 1_000_000;
    case "kHz":
      return hz / 1_000;
    default:
      return hz;
  }
}

const chartConfig = {
  chartConfig: {
    label: "chartConfig",
    color: "hsl(var(--primary))",
  },
} satisfies ChartConfig;

export function renderGraph({
  platformName,
  benchName,
  dataset,
}: {
  platformName: string;
  benchName: string;
  dataset: FormattedDataSetEntry[];
}) {
  const frequencyUnit = determineUnit(dataset.map((entry) => entry.bench.value));

  const chartData = dataset.map((entry) => {
    const value = convertToUnit(entry.bench.value, frequencyUnit);

    return {
      commit: entry.commit.id.slice(0, 7),
      rawValue: entry.bench.value,
      value,
      unit: frequencyUnit,
      commitUrl: entry.commit.url,
      commitMessage: entry.commit.message,
      commitTimestamp: entry.commit.timestamp,
      committer: entry.commit.committer.username,
    };
  });

  const maxValue = Math.max(...chartData.map((d) => d.value));
  const yAxisMax = roundToNiceNumber(maxValue * 1.2);

  return (
    <Card id={`${platformName}-${benchName}`} className="relative w-full border-none bg-transparent pt-8">
      <CardHeader className="pt-0">
        <CardTitle className="flex flex-row items-baseline gap-5">
          <span className="font-mono">{benchName}</span>
          <span className="text-muted-foreground text-xs capitalize">{joinWords(platformName)}</span>
        </CardTitle>
      </CardHeader>
      <CardContent>
        <ChartContainer config={chartConfig} className="h-[320px] w-full">
          <AreaChart
            accessibilityLayer
            data={chartData}
            margin={{
              left: 12,
            }}
          >
            <CartesianGrid />
            <defs>
              <linearGradient id="fill" x1="0" y1="0" x2="0" y2="1">
                <stop offset="5%" stopColor="var(--color-chartConfig)" stopOpacity={1} />
                <stop offset="95%" stopColor="var(--color-chartConfig)" stopOpacity={0.6} />
              </linearGradient>
            </defs>

            <Area
              animationDuration={500}
              dataKey="value"
              type="monotone"
              fill="url(#fill)"
              fillOpacity={0.2}
              stroke="var(--color-chartConfig)"
              activeDot={{
                r: 8,
                cursor: "pointer",
                // @ts-expect-error -- ignore
                onClick: (_, { index }) => {
                  if (chartData[index]?.commitUrl) {
                    window.open(chartData[index].commitUrl);
                  }
                },
              }}
            />

            <XAxis dataKey="commit" tickLine={false} axisLine={false} />

            <YAxis dataKey="value" tickLine={false} axisLine={false} domain={[0, yAxisMax]}>
              <Label angle={270} position="left" style={{ textAnchor: "middle" }}>
                {frequencyUnit}
              </Label>
            </YAxis>

            <ChartTooltip
              cursor={false}
              content={
                // @ts-expect-error -- ignore
                <CustomTooltip />
              }
            />
          </AreaChart>
        </ChartContainer>
      </CardContent>
    </Card>
  );
}
