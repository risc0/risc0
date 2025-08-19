import { shuffle } from "es-toolkit";
import { getAllProjects } from "@/libs/notion/get-all-projects";
import { ProjectListItem } from "./project-list-item";

export async function EcosystemPageContent() {
  const projects = await getAllProjects();

  if (!projects) {
    return null;
  }

  const filteredProjects = projects.filter((partner) => partner.pageCover);

  return shuffle(filteredProjects).map((project) => <ProjectListItem key={project.id} project={project} />);
}
