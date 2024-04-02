import { z } from "zod";

const cratesIoValidationTableSchema = z.object({
  name: z.string(),
  version: z.string(),
  status: z.string(),
  custom_profile: z.string(),
  build_errors: z.string().optional(),
});

export type CratesIoValidationTable = z.infer<typeof cratesIoValidationTableSchema>;
