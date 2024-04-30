import { z } from "zod";

const datasheetTableSchema = z.object({
  cycles: z.number(),
  duration: z.number(),
  hashfn: z.string(),
  name: z.string(),
  ram: z.number(),
  seal: z.number(),
  throughput: z.number(),
  total_cycles: z.number(),
  user_cycles: z.number(),
});

export type DatasheetTableSchema = z.infer<typeof datasheetTableSchema>;
