import { z } from "zod";

const baseSchema = z.object({
  name: z.string(),
  size: z.string(),
  speed: z.string(),
  total_duration: z.string().transform(val => Number(val)),
  total_cycles: z.string().transform(val => Number(val)),
  user_cycles: z.string().transform(val => Number(val)),
  proof_bytes: z.string().transform(val => Number(val)),
});

const release0_21Schema = baseSchema.extend({
  job_name: z.string(),
  job_size: z.string(),
  exec_duration: z.string().transform(val => Number(val)),
  proof_duration: z.string().transform(val => Number(val)),
  verify_duration: z.string().transform(val => Number(val)),
  insn_cycles: z.string().transform(val => Number(val)),
  prove_cycles: z.string().transform(val => Number(val)),
});

const versions = ["main", "release-0.21", "release-1.0", "release-1.1", "release-1.2", "release-2.0"] as const;

const applicationsBenchmarksTableSchema = Object.fromEntries(
  versions.map(version => [
    version,
    version === "release-0.21" ? release0_21Schema : baseSchema
  ])
);

export type ApplicationsBenchmarksTableSchema<T extends keyof typeof applicationsBenchmarksTableSchema> = z.infer<
  (typeof applicationsBenchmarksTableSchema)[T]
>;
