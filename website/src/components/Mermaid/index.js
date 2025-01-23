import ExecutionEnvironment from "@docusaurus/ExecutionEnvironment";
import { useColorMode } from "@docusaurus/theme-common";
import mermaid from "mermaid";
import React, { useEffect, useId } from "react";

export default function Mermaid({ definition, height = 280 }) {
  const id = useId();
  const { isDarkTheme } = useColorMode();

  // biome-ignore lint/correctness/useExhaustiveDependencies: ignore
  useEffect(() => {
    if (ExecutionEnvironment.canUseDOM) {
      import("svg-pan-zoom")
        .then((module) => {
          const svgPanZoom = module.default;
          const drawDiagram = async () => {
            const element = document.querySelector(
              `#${CSS.escape(id)}-mermaid`,
            );

            mermaid.initialize({
              theme: isDarkTheme ? "dark" : "default",
            });

            const { svg } = await mermaid.render(
              "mermaid-svg-id",
              definition.replace(/```mermaid/, ""),
            );
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
  }, [isDarkTheme]);

  return (
    <div
      id={`${id}-mermaid`}
      className="mermaid-graph"
      style={{
        height: Number(height),
        borderRadius: 12,
        cursor: "grab",
        "&:active": {
          cursor: "grabbing",
        },
      }}
    />
  );
}
