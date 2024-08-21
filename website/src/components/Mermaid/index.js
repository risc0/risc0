import React, { useEffect, useId } from "react";
import mermaid from 'https://cdn.jsdelivr.net/npm/mermaid@10/dist/mermaid.esm.min.mjs';
import 'https://cdn.jsdelivr.net/npm/svg-pan-zoom/dist/svg-pan-zoom.min.js';

mermaid.initialize({ startOnLoad: false, theme: "default" });

export default function Mermaid({ definition, height = 280 }) {
  const id = useId()

  useEffect(() => {
    const drawDiagram = async function () {
      const element = document.querySelector(`#${CSS.escape(id)}-mermaid`);
      const { svg } = await mermaid.render('mermaid-svg-id', definition);
      element.innerHTML = svg.replace(/[ ]*max-width:[ 0-9\.]*px;/i , '');

      svgPanZoom('#mermaid-svg-id', {
        zoomEnabled: true,
        controlIconsEnabled: true,
        fit: true,
        center: true,
        dblClickZoomEnabled: false,
      })
    };

    drawDiagram();
  }, [])

  return (
    <div id={`${id}-mermaid`} className="mermaid-graph" style={{ height: Number(height), borderRadius: 12 }}/>
  );
}
