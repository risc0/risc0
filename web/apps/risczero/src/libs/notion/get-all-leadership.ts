import type { Leadership } from "@/app/blog/_types";
import { fetchNotionData } from "./fetch-notion-data";

export const getAllLeadership = () => fetchNotionData<Leadership>("aaab227104ee43e0b2eb0724ba33620d");
