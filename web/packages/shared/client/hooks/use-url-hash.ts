"use client";

import { useEffect, useState } from "react";

function getHash() {
  return window.location.hash.slice(1);
}

export function useUrlHash() {
  const [urlHash, setUrlHash] = useState<string>(() => (typeof window !== "undefined" ? getHash() : ""));

  useEffect(() => {
    function handleHashChange() {
      setUrlHash(getHash());
    }

    window.addEventListener("hashchange", handleHashChange);
    window.addEventListener("popstate", handleHashChange);

    // Handle hash changes caused by manual URL updates
    const intervalId = setInterval(() => {
      if (getHash() !== urlHash) {
        setUrlHash(getHash());
      }
    }, 0); // 0ms to avoid race condition

    return () => {
      window.removeEventListener("hashchange", handleHashChange);
      window.removeEventListener("popstate", handleHashChange);

      clearInterval(intervalId);
    };
  }, [urlHash]);

  return urlHash;
}
