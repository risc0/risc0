import React, { useEffect, useId } from "react";
import mermaid from "../../../node_modules/mermaid/dist/mermaid.esm.min.mjs";
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

            console.log("mermaid.initialize", mermaid);

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

            module.default("#mermaid-svg-id", {
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
