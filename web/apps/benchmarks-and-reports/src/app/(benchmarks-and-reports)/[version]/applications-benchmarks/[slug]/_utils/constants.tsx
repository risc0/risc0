import type { Version } from "~/types/version";

export const APPLICATIONS_BENCHMARKS_FILENAMES_TO_TITLES: {
  [K in Version]: {
    [key: string]: string;
  };
} = {
  main: {
    "macOS-apple_m2_pro.csv": "Metal on Apple M2 Pro",
    "Linux-nvidia_rtx_3090_ti.csv": "CUDA on NVIDIA RTX 3090 Ti",
    "macOS-cpu.csv": "CPU only on Apple M2 Pro",
    "Linux-cpu.csv": "CPU only on c6i.8xlarge",
    "Linux-g6.xlarge.csv": "CUDA on g6.xlarge",
  },
  "release-0.21": {
    "macOS-apple_m2_pro.csv": "Metal on Apple M2 Pro",
    "Linux-nvidia_rtx_a5000.csv": "CUDA on NVIDIA RTX A5000",
    "macOS-cpu.csv": "CPU only on Apple M2 Pro",
    "Linux-cpu.csv": "CPU only on c6i.8xlarge",
  },
  "release-1.0": {
    "macOS-apple_m2_pro.csv": "Metal on Apple M2 Pro",
    "Linux-nvidia_rtx_3090_ti.csv": "CUDA on NVIDIA RTX 3090 Ti",
    "macOS-cpu.csv": "CPU only on Apple M2 Pro",
    "Linux-cpu.csv": "CPU only on c6i.8xlarge",
  },
} as const satisfies Record<Version, Record<string, string>>;
