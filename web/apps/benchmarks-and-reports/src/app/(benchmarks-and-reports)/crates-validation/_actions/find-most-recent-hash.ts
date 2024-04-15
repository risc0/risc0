"use server";

export async function findMostRecentHash() {
  const response = await fetch("https://risc0.github.io/ghpages/dev/crate-validation/results/index.json");
  const responseText = await response.text();

  // Find the most recent timestamp
  const mostRecent = JSON.parse(responseText.replace("[,", "[")).reduce((prev, current) =>
    prev.timestamp > current.timestamp ? prev : current,
  );

  // Retrieve the hash related to the most recent timestamp
  return mostRecent.hash;
}
