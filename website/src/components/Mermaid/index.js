import React, { useEffect, useId } from "react";
import mermaid from "mermaid/dist/mermaid.esm.min.mjs";
import ExecutionEnvironment from "@docusaurus/ExecutionEnvironment";

export default function Mermaid({ definition, height = 280 }) {
  const id = useId();

  useEffect(() => {
    if (ExecutionEnvironment.canUseDOM) {
      import("svg-pan-zoom/dist/svg-pan-zoom.min.js")
        .then((module) => {
          const drawDiagram = async function () {
            const element = document.querySelector(
              `#${CSS.escape(id)}-mermaid`,
            );
            const { svg } = await mermaid.render("mermaid-svg-id", definition);
            element.innerHTML = svg.replace(/[ ]*max-width:[ 0-9\.]*px;/i, "");

            module.default("#mermaid-svg-id", {
              zoomEnabled: true,
              controlIconsEnabled: true,
              fit: true,
              center: true,
              dblClickZoomEnabled: false,
            });
          };

          drawDiagram();
          // Initialize svgPanZoom or use it as needed
        })
        .catch((error) => {
          console.error("Error loading svg-pan-zoom:", error);
        });
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
