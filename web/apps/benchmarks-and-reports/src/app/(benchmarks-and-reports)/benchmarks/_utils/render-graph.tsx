import truncate from "lodash-es/truncate";
import Chart from "react-chartjs-2";
import type { FormattedDataSetEntry } from "./collect-benches-per-test-case";

const TOOL_COLORS = {
  customBiggerIsBetter: "#020077",
};

export function renderGraph({
  platformName,
  benchName,
  dataset,
}: { platformName: string; benchName: string; dataset: FormattedDataSetEntry[] }) {
  // biome-ignore lint/style/noNonNullAssertion: ignore
  const color = TOOL_COLORS[dataset.length > 0 ? dataset[0]!.tool : "_"];

  const data = {
    labels: dataset.map((d) => d.commit.id.slice(0, 7)),
    datasets: [
      {
        label: benchName,
        data: dataset.map((d) => d.bench.value),
        borderColor: color,
        borderWidth: 1,
        fill: true,
        backgroundColor: `${color}50`, // Add alpha for #rrggbbaa
      },
    ],
  };

  const options = {
    animation: {
      duration: 0, // general animation time
    },
    hover: {
      animationDuration: 0, // duration of animations when hovering an item
    },
    responsive: true,
    maintainAspectRatio: false,
    responsiveAnimationDuration: 0, // animation duration after a resize
    scales: {
      xAxes: [
        {
          scaleLabel: {
            display: true,
            labelString: "commit",
          },
        },
      ],
      yAxes: [
        {
          scaleLabel: {
            display: true,
            // biome-ignore lint/style/noNonNullAssertion: ignore
            labelString: dataset.length > 0 ? dataset[0]!.bench.unit : "",
          },
          ticks: {
            beginAtZero: true,
          },
        },
      ],
    },
    onClick: (_mouseEvent, activeElems) => {
      if (activeElems.length === 0) {
        return;
      }

      const index = activeElems[0]._index;
      // biome-ignore lint/style/noNonNullAssertion: ignore
      const url = dataset[index]!.commit.url;

      window.open(url, "_blank");
    },
    onHover: (event, chartElement) => {
      event.target.style.cursor = chartElement[0] ? "pointer" : "default";
    },
    tooltips: {
      backgroundColor: "rgb(8, 8, 8)",
      callbacks: {
        afterTitle: (items) => {
          const { index } = items[0];
          const data = dataset[index];

          return data
            ? `\n${truncate(data.commit.message, {
                length: 140,
                omission: "…",
              })}\n\n${data.commit.timestamp} committed by @${data.commit.committer.username}\n`
            : "";
        },
        label: (item) => {
          let label = item.value;
          // biome-ignore lint/style/noNonNullAssertion: ignore
          const { range, unit } = dataset[item.index]!.bench;

          label += ` ${unit}`;

          if (range) {
            label += ` (${range})`;
          }

          return label;
        },
      },
    },
  };

  return (
    <div className="relative min-h-80 w-full">
      <Chart id={`${platformName}-${benchName}`} type="line" data={data} options={options} />
    </div>
  );
}
