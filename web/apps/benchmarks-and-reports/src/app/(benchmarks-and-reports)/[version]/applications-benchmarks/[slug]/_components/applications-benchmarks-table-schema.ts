import { z } from "zod";

const applicationsBenchmarksTableSchema = {
  main: z.object({
    name: z.string(),
    size: z.string(),
    speed: z.string(),
    total_duration: z.string(),
    total_cycles: z.string(),
    user_cycles: z.string(),
    proof_bytes: z.string(),
  }),
  "release-0.21": z.object({
    job_name: z.string(),
    job_size: z.string(),
    exec_duration: z.string(),
    proof_duration: z.string(),
    total_duration: z.string(),
    verify_duration: z.string(),
    insn_cycles: z.string(),
    prove_cycles: z.string(),
    proof_bytes: z.string(),
  }),
  "release-1.0": z.object({
    name: z.string(),
    size: z.string(),
    speed: z.string(),
    total_duration: z.string(),
    total_cycles: z.string(),
    user_cycles: z.string(),
    proof_bytes: z.string(),
  }),
  "release-1.1": z.object({
    name: z.string(),
    size: z.string(),
    speed: z.string(),
    total_duration: z.string(),
    total_cycles: z.string(),
    user_cycles: z.string(),
    proof_bytes: z.string(),
  }),
  "release-1.2": z.object({
    name: z.string(),
    size: z.string(),
    speed: z.string(),
    total_duration: z.string(),
    total_cycles: z.string(),
    user_cycles: z.string(),
    proof_bytes: z.string(),
  }),
  "release-2.0": z.object({
    name: z.string(),
    size: z.string(),
    speed: z.string(),
    total_duration: z.string(),
    total_cycles: z.string(),
    user_cycles: z.string(),
    proof_bytes: z.string(),
  }),
};

export type ApplicationsBenchmarksTableSchema<T extends keyof typeof applicationsBenchmarksTableSchema> = z.infer<
  (typeof applicationsBenchmarksTableSchema)[T]
>;
