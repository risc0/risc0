"use client";

import { useEffect, useState } from "react";

export function useMousePosition() {
  const [mousePosition, setMousePosition] = useState({ x: null, y: null });

  useEffect(() => {
    function updateMousePosition(event) {
      setMousePosition({ x: event.clientX, y: event.clientY });
    }

    window.addEventListener("mousemove", updateMousePosition);

    return () => {
      window.removeEventListener("mousemove", updateMousePosition);
    };
  }, []);

  return mousePosition;
}
