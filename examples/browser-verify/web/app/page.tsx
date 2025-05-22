"use client";

import { useState, useCallback } from "react";
import { Button } from "@/components/ui/button";
import { TabbedCodeBlock } from "@/components/tabbed-code-block";

type Tab = "fibonacci" | "wasm";
const TARGET_N = 1_000_000;

/** Return no. of digits and time taken to calculate for the nth Fibonacci number. */
function calculateFibbonaci(n: number): { digits: number, timeMs: number } {
  let a = 0n,
    b = 1n;
  const start = performance.now();

  for (let i = 0; i < n; i++) {
    [a, b] = [b, a + b];
  }

  return {
    digits: a.toString().length,
    timeMs: performance.now() - start,
  };
}

export default function Home() {
  const [activeTab, setActiveTab] = useState<Tab>("wasm");
  const [fibMsg, setFibMsg] = useState<string | null>(null);
  const [fibTimeMs, setFibTimeMs] = useState<number | null>(null);
  const [proofMsg, setProofMsg] = useState<string | null>(null);

  const renderMsg = (msg: string | null) =>
    msg && (
      <div className="mt-4 flex flex-col gap-2">
        {msg.split("\n").map((line, i) => (
          <p
            key={i}
            className={i === 0 ? "text-center font-medium" : "whitespace-pre-line"}
          >
            {line}
          </p>
        ))}
      </div>
    );

  const handleFib = useCallback(() => {
    setFibMsg("Calculating…");

    setTimeout(() => {
      const { digits, timeMs } = calculateFibbonaci(TARGET_N);
      setFibTimeMs(timeMs);

      setFibMsg(
        `${TARGET_N.toLocaleString()}th Fibonacci has ${digits.toLocaleString()} digits (calculated in ${(timeMs / 1000).toFixed(3)} s)`
      );
    }, 0);
  }, []);

  const handleVerify = useCallback(async () => {
    setProofMsg("Verifying proof…");

    const { default: init, verify_proof } = await import(
      /* webpackIgnore: true */ "/wasm/pkg/verifier.js"
    );

    await init();

    const [proofBuf, imageIdBuf] = await Promise.all(
      ["/proof_data/receipt.bin", "/proof_data/image_id.bin"].map(async (url) => {
        const res = await fetch(url);
        return new Uint8Array(await res.arrayBuffer());
      })
    );

    const start = performance.now();
    try {
      const digits = verify_proof(proofBuf, imageIdBuf);
      const timeMs = performance.now() - start;

      let msg = `Proof verified in ${timeMs.toFixed(2)} ms\nThe ${TARGET_N.toLocaleString()}th Fibonacci number was proven to have ${digits.toLocaleString()} digits.`;

      if (fibTimeMs !== null) {
        msg += `\nProof verification was ${(fibTimeMs / timeMs).toFixed(
          2
        )}× faster than calculating locally.`;
      }

      setProofMsg(msg);
    } catch (e) {
      console.error(e);
      setProofMsg("Proof verification failed");
    }
  }, [fibTimeMs]);

  return (
    <main className="flex flex-col items-center gap-4 p-6">
      <TabbedCodeBlock activeTab={activeTab} onTabChange={setActiveTab} />

      {activeTab === "fibonacci" && (
        <>
          <Button onClick={handleFib}>
            Calculate {TARGET_N.toLocaleString()}th Fibonacci
          </Button>
          {renderMsg(fibMsg)}
        </>
      )}

      {activeTab === "wasm" && (
        <>
          <Button onClick={handleVerify}>Verify Proof</Button>
          {renderMsg(proofMsg)}
        </>
      )}
    </main>
  );
}

