import Link from "next/link";
import type { ReactNode } from "react";
import type { Version } from "~/types/version";

export const DATASHEET_FILENAMES_TO_TITLES: {
  [K in Version]: {
    [key: string]: ReactNode;
  };
} = {
  main: {
    "macOS-apple_m2_pro.json": "Metal on Apple M2 Pro",
    "macOS-cpu.json": "CPU only on Apple M2 Pro",
    "Linux-nvidia_rtx_3090_ti.json": "CUDA on NVIDIA RTX 3090 Ti",
    "Linux-g6.xlarge.json": (
      <>
        CUDA on{" "}
        <Link
          rel="noopener noreferrer"
          target="_blank"
          href="https://instances.vantage.sh/aws/ec2/g6.xlarge"
          className="link"
        >
          g6.xlarge
        </Link>
      </>
    ),
    "Linux-cpu.json": (
      <>
        CPU only on{" "}
        <Link
          rel="noopener noreferrer"
          target="_blank"
          href="https://instances.vantage.sh/aws/ec2/c6i.8xlarge"
          className="link"
        >
          c6i.8xlarge
        </Link>
      </>
    ),
  },
  "release-0.21": {
    "macOS-apple_m2_pro.json": "Metal on Apple M2 Pro",
    "Linux-nvidia_rtx_3090_ti.json": "CUDA on NVIDIA RTX 3090 Ti",
    "macOS-cpu.json": "CPU only on Apple M2 Pro",
    "Linux-cpu.json": (
      <>
        CPU only on{" "}
        <Link
          rel="noopener noreferrer"
          target="_blank"
          href="https://instances.vantage.sh/aws/ec2/c6i.8xlarge"
          className="link"
        >
          c6i.8xlarge
        </Link>
      </>
    ),
  },
  "release-1.0": {
    "macOS-apple_m2_pro.json": "Metal on Apple M2 Pro",
    "Linux-nvidia_rtx_3090_ti.json": "CUDA on NVIDIA RTX 3090 Ti",
    "macOS-cpu.json": "CPU only on Apple M2 Pro",
    "Linux-cpu.json": (
      <>
        CPU only on{" "}
        <Link
          rel="noopener noreferrer"
          target="_blank"
          href="https://instances.vantage.sh/aws/ec2/c6i.8xlarge"
          className="link"
        >
          c6i.8xlarge
        </Link>
      </>
    ),
  },
} as const satisfies Record<Version, Record<string, ReactNode>>;
