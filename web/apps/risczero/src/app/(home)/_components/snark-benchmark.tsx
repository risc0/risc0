"use client";

import { Subtitle } from "@/app/_components/subtitle";
import { Badge } from "@risc0/ui/badge";
import { cn } from "@risc0/ui/cn";
import { CheckIcon, SquareIcon } from "lucide-react";
import { useInView } from "motion/react";
import { useEffect, useRef, useState } from "react";
import { SnarkExamples } from "./snark-examples";

const SNARK_GENERATION_TIME_SECONDS = 12;
const ANIMATION_SPEED_MULTIPLIER = 2.5; // How much faster the animation runs
const OTHER_COMPLETION_PERCENTAGE = 80; // The "Other" bar goes up to 80%

function SnarkBenchmarkGraph() {
  const progressRef = useRef<HTMLDivElement>(null);
  const [completed, setCompleted] = useState<boolean>(false);
  const [isMounted, setIsMounted] = useState<boolean>(false);
  const startTimeRef = useRef<number | null>(null);

  useEffect(() => {
    setIsMounted(true);
    startTimeRef.current = Date.now();

    setTimeout(
      () => {
        setCompleted(true);
      },
      (SNARK_GENERATION_TIME_SECONDS * 1000) / ANIMATION_SPEED_MULTIPLIER,
    );
  }, []);

  useEffect(() => {
    if (!isMounted) {
      return;
    }

    const progressElement = progressRef.current;
    let animation: Animation | undefined;

    function updateProgress() {
      if (!animation && progressElement) {
        animation = progressElement.getAnimations()[0];
      }

      if (animation && progressElement) {
        const currentTime = Date.now();
        const elapsedTime = startTimeRef.current ? currentTime - startTimeRef.current : 0;
        const totalSeconds = Math.floor(elapsedTime / 400); // 2.5x speed
        const minutes = Math.floor(totalSeconds / 60);
        const seconds = totalSeconds % 60;

        progressElement.textContent = `${minutes ? `${minutes}m ` : ""}${minutes ? String(seconds).padStart(2, "0") : seconds}s`;

        if (animation.playState === "finished") {
          clearInterval(intervalId);
          progressElement.style.display = "none";
        }
      }
    }

    const intervalId = setInterval(updateProgress, 400);

    updateProgress();

    return () => {
      clearInterval(intervalId);
    };
  }, [isMounted]);

  return (
    <>
      <style>
        {`
        @keyframes bench0-anim {
          0% {
            left: 0
          }

          to {
            left: ${OTHER_COMPLETION_PERCENTAGE}%
          }
        }

        @keyframes scale-bar {
          0% {
            transform: scaleX(.0000001)
          }

          to {
            transform: scale(1)
          }
        }

        #progress {
          animation: bench0-anim 96s linear;  /* 2.5x speed */
          left: 80%
        }

        .bar01 {
          animation: scale-bar 1s linear;  /* 2.5x speed */
          transform-origin: left
        }

        .bar02 {
          animation: scale-bar 4.8s linear; /* 2.5x speed */
          transform-origin: left
        }

        .bar03 {
          animation: scale-bar 1s linear; /* 2.5x speed */
          transform-origin: left
        }

        .bar04 {
          animation: scale-bar 96s linear; /* 2.5x speed */
          transform-origin: left
        }
        `}
      </style>
      <div className="flex w-full animate-fade-in-left flex-col">
        <div className="mb-8 flex flex-row items-start justify-center gap-8 md:justify-between">
          <div className="space-y-1.5">
            <Subtitle className="line-clamp-2 max-w-none text-center md:text-left md:text-lg" as="h4">
              Blazing Fast Small Proofs, Courtesy of Our SNARK Wrapper
            </Subtitle>
            <figcaption className="line-clamp-3 text-center text-muted-foreground text-sm italic md:text-left">
              Time it takes to wrap our STARKs with a SNARK (2.5x speed)
              <br />
              Tested on a c7a.32xl instance
            </figcaption>
          </div>

          <SnarkExamples />
        </div>

        <figure className="relative h-[160px] w-full overflow-hidden text-[13px] leading-[20px]">
          <div className="-right-28 absolute top-0 left-[90px] h-[110px]">
            <div className="absolute inset-y-0 left-0 w-[1px] bg-[rgba(127,127,127,0.25)]" />
            <div className="absolute inset-y-0 left-[20%] w-[1px] bg-[rgba(127,127,127,0.25)]" />
            <div className="absolute inset-y-0 left-[40%] w-[1px] bg-[rgba(127,127,127,0.25)]" />
            <div className="absolute inset-y-0 left-[60%] w-[1px] bg-[rgba(127,127,127,0.25)]" />
            <div className="absolute inset-y-0 left-[80%] w-[1px] bg-[rgba(127,127,127,0.25)] opacity-0" />
            <div className="absolute inset-y-0 left-full w-[1px] bg-[rgba(127,127,127,0.25)] opacity-0" />

            <div className="absolute top-[23px] left-0 h-[24px] w-[4%] border-2 border-border bg-[rgba(191,191,191,0.1)] dark:border-none" />
            <div className="bar01 absolute top-[23px] left-0 z-10 h-[24px] w-[0.83%] bg-muted-foreground transition-colors" />
            <div
              className={cn(
                "bar02 absolute top-[23px] left-0 h-[24px] w-[4%] border-2 border-neutral-500 bg-[#fdff9d] transition-all duration-1000 dark:border-none dark:bg-primary",
                completed && "rounded",
              )}
            />
            <div className="absolute top-[24px] right-full mr-4 h-[20px] w-[90px] whitespace-nowrap text-right font-bold text-[18px]">
              RISC Zero
            </div>

            {completed && (
              <Badge
                variant="secondary"
                className="absolute top-[24px] left-[5.16%] ml-2 flex animate-fade-in-left flex-row items-center gap-1 p-0 px-2 text-[10px] shadow-sm duration-500"
              >
                <CheckIcon className="size-3" />
                SNARK Generated in {SNARK_GENERATION_TIME_SECONDS}s
              </Badge>
            )}

            <div className="absolute top-[69px] left-0 h-[24px] w-4/5 border-2 border-border bg-gradient-to-r from-70% from-[rgba(191,191,191,0.1)] dark:border-none" />
            <div className="bar03 absolute top-[69px] left-0 z-10 h-[24px] w-[0.83%] bg-muted-foreground" />
            <div className="bar04 absolute top-[69px] left-0 h-[24px] w-4/5 border-2 border-neutral-500 border-r-transparent bg-[#fdff9d] dark:border-none dark:bg-primary" />
            <div className="absolute top-[70px] right-full mr-4 h-[30px] w-[90px] whitespace-nowrap text-right text-[18px]">
              Other
            </div>

            <div className="absolute top-[114px] left-0 ml-[-25px] w-[50px] text-center font-mono text-muted-foreground">
              0m
            </div>
            <div className="absolute top-[114px] left-[20%] ml-[-25px] w-[50px] text-center font-mono text-muted-foreground">
              1m
            </div>
            <div className="absolute top-[114px] left-[40%] ml-[-25px] w-[50px] text-center font-mono text-muted-foreground">
              2m
            </div>
            <div className="absolute top-[114px] left-[60%] ml-[-25px] w-[50px] text-center font-mono text-muted-foreground">
              3m
            </div>
            <div className="absolute top-[114px] left-[80%] ml-[-25px] w-[50px] text-center font-mono text-muted-foreground opacity-0">
              4m
            </div>
            <div className="absolute top-[114px] left-full ml-[-25px] w-[50px] text-center font-mono text-muted-foreground opacity-0">
              5m
            </div>
            <div
              id="progress"
              className="-translate-x-1/2 absolute top-[114px] px-4 text-center font-mono"
              style={{
                background:
                  "linear-gradient(to right,rgba(255, 255, 255, 0) 0%, hsl(var(--background)) 25%, hsl(var(--background)) 75%, rgba(255, 255, 255, 0) 100%)",
              }}
              ref={progressRef}
            >
              0s
            </div>
          </div>
        </figure>

        <div className="flex flex-row items-center justify-start gap-12 pt-2 pl-[90px]">
          <p className="flex flex-row items-center gap-2">
            <SquareIcon className="size-5 rounded bg-muted-foreground text-transparent" />
            <span>STARK</span>
          </p>
          <p className="flex flex-row items-center gap-2">
            <SquareIcon className="size-5 rounded border-2 border-neutral-500 bg-[#fdff9d] darl:bg-primary text-transparent dark:border-none" />
            <span>SNARK</span>
          </p>
        </div>
      </div>
    </>
  );
}

export function SnarkBenchmark() {
  const ref = useRef<HTMLDivElement>(null);
  const isInView = useInView(ref, { once: true, margin: "0px" });

  return (
    <div ref={ref} className="w-full">
      {isInView && <SnarkBenchmarkGraph />}
    </div>
  );
}
