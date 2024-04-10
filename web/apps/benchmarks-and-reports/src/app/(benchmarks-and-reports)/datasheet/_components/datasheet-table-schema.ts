import { z } from "zod";

const datasheetTableSchema = z.object({
  cycles: z.number(),
  user_cycles: z.number(),
  total_cycles: z.number(),
  duration: z.number(),
  ram: z.number(),
  seal: z.number(),
  throughput: z.number(),
});

export type DatasheetTableSchema = z.infer<typeof datasheetTableSchema>;
