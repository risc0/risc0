"use server";

export default async function fetchDatasheetCommitHash() {
  try {
    const response = await fetch("https://risc0.github.io/ghpages/dev/datasheet/COMMIT_HASH.txt");
    return await response.text();
  } catch (error) {
    console.error("Error fetching commit hash:", error);
  }
}
