import ExecutionEnvironment from "@docusaurus/ExecutionEnvironment";
import mermaid from "mermaid";
import React, { useEffect, useId } from "react";

export default function Mermaid({ definition, height = 280 }) {
  const id = useId();

  // biome-ignore lint/correctness/useExhaustiveDependencies: ignore
  useEffect(() => {
    if (ExecutionEnvironment.canUseDOM) {
      import("svg-pan-zoom")
        .then((module) => {
          const svgPanZoom = module.default; // Extract the default export
          const drawDiagram = async () => {
            const element = document.querySelector(
              `#${CSS.escape(id)}-mermaid`,
            );

            mermaid.initialize({
              theme: "dark",
              themeVariables: {
                fontSize: "12px",
                fontFamily: "var(--ifm-heading-font-family)",
                nodeTextColor: "var(--ifm-color-emphasis-100)",
              },
            });

            const { svg } = await mermaid.render("mermaid-svg-id", definition);
            element.innerHTML = svg.replace(/[ ]*max-width:[ 0-9\.]*px;/i, "");

            svgPanZoom(document.getElementById("mermaid-svg-id"), {
              zoomEnabled: true,
              controlIconsEnabled: true,
              fit: true,
              center: true,
              dblClickZoomEnabled: false,
            });
          };

          drawDiagram();
        })
        .catch(console.error);
    }
  }, []);

  return (
    <div
      id={`${id}-mermaid`}
      className="mermaid-graph"
      style={{ height: Number(height), borderRadius: 12 }}
    />
  );
}
