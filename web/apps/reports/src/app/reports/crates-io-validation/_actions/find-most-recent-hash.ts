"use server";

export default async function findMostRecentHash() {
  try {
    const response = await fetch("https://risc0.github.io/ghpages/dev/crate-validation/results/index.json");
    const responseText = await response.text();

    // Find the most recent timestamp
    const mostRecent = JSON.parse(responseText.replace("[,", "[")).reduce((prev, current) =>
      prev.timestamp > current.timestamp ? prev : current,
    );

    // Retrieve the hash related to the most recent timestamp
    const mostRecentHash = mostRecent.hash;

    return mostRecentHash;
  } catch (error) {
    console.error("Error fetching commit hash:", error);
  }
}
