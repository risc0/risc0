"use client";

import { useEffect, useRef } from "react";

export function useInterval(callback: () => void, delay: number | null) {
  const savedCallback = useRef(callback);

  useEffect(() => {
    savedCallback.current = callback;
  }, [callback]);

  useEffect(() => {
    function tick() {
      savedCallback.current();
    }

    if (delay !== null) {
      tick();

      const id = setInterval(tick, delay);

      return () => {
        clearInterval(id);
      };
    }
  }, [delay]);
}
