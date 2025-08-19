import type { Investor } from "@/app/blog/_types";
import { fetchNotionData } from "./fetch-notion-data";

export const getAllInvestors = () => fetchNotionData<Investor>("1b47bc6221e848d6add8ffb74c9bd255");
