"use server";

export async function fetchDatasheetCommitHash() {
  const response = await fetch("https://risc0.github.io/ghpages/dev/datasheet/COMMIT_HASH.txt", {
    next: { revalidate: 3600 },
  });
  const responseText = await response.text();

  return responseText;
}
