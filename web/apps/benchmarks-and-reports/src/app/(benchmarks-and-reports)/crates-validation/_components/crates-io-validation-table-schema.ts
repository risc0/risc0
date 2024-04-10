import { z } from "zod";

const cratesIoValidationTableSchema = z.object({
  name: z.string(),
  version: z.string(),
  status: z.enum(["Success", "BuildFail", "RunFail", "Skipped"]),
  custom_profile: z.string(),
  build_errors: z.string().optional(),
});

export type CratesIoValidationTableSchema = z.infer<typeof cratesIoValidationTableSchema>;
