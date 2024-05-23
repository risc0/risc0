import { z } from "zod";

const applicationsBenchmarksTableSchema = z.object({
  name: z.string(),
  size: z.string(),
  speed: z.string(),
  total_duration: z.string(),
  total_cycles: z.string(),
  user_cycles: z.string(),
  proof_bytes: z.string(),
});

export type ApplicationsBenchmarksTableSchema = z.infer<typeof applicationsBenchmarksTableSchema>;
