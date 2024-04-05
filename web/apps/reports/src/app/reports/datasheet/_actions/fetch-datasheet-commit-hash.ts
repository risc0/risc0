"use server";

export async function fetchDatasheetCommitHash() {
  const response = await fetch("https://risc0.github.io/ghpages/dev/datasheet/COMMIT_HASH.txt");
  const responseText = await response.text();

  return responseText;
}
