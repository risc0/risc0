import { z } from "zod";

const applicationsBenchmarksTableSchema = z.object({
  job_name: z.string(),
  job_size: z.string(),
  exec_duration: z.string(),
  proof_duration: z.string(),
  total_duration: z.string(),
  verify_duration: z.string(),
  insn_cycles: z.string(),
  prove_cycles: z.string(),
  proof_bytes: z.string(),
});

export type ApplicationsBenchmarksTableSchema = z.infer<typeof applicationsBenchmarksTableSchema>;
