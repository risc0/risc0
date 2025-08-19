import type { Project } from "@/app/blog/_types";
import { fetchNotionData } from "./fetch-notion-data";

export const getAllProjects = () => fetchNotionData<Project>("1ecf77fbe2a94ffb93b53bde15975666");
