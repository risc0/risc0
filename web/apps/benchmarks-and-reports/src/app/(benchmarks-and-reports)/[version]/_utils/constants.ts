export const CRATES_VALIDATION_DESCRIPTION = "View the latest Crates.io validation results";
export const BENCHMARKS_DESCRIPTION = "View the latest benchmarks for the RISC Zero platform";
export const APPLICATIONS_BENCHMARKS_DESCRIPTION = "View the latest applications benchmarks for the RISC Zero platform";
export const DATASHEET_DESCRIPTION = "View the latest datasheet for the RISC Zero platform";

export const REPORTS = [
  {
    label: "Crates.io Validation",
    href: "/crates-validation",
    description: CRATES_VALIDATION_DESCRIPTION,
  },
  {
    label: "Benchmarks",
    href: "/benchmarks",
    description: BENCHMARKS_DESCRIPTION,
  },
  {
    label: "Applications Benchmarks",
    href: "/applications-benchmarks",
    description: APPLICATIONS_BENCHMARKS_DESCRIPTION,
  },
  {
    label: "Datasheet",
    href: "/datasheet",
    description: DATASHEET_DESCRIPTION,
  },
] as const;
