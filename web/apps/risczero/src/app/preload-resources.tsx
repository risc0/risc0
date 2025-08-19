"use client";

import ReactDOM from "react-dom";

export function PreloadResources() {
  ReactDOM.preload("/misc/planet-dark.webp", { as: "image" });

  return null;
}
