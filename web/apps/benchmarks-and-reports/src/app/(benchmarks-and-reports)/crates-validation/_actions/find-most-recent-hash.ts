import "server-only";

export async function findMostRecentHash() {
  const response = await fetch(
    "https://raw.githubusercontent.com/risc0/ghpages/main/dev/crate-validation/results/index.json",
    {
      headers: {
        Accept: "application/vnd.github.v3.raw",
      },
      cache: "force-cache",
      next: { revalidate: 900 },
    },
  );
  const responseText = await response.text();

  // Find the most recent timestamp
  const mostRecent = JSON.parse(responseText.replace("[,", "[")).reduce((prev, current) =>
    prev.timestamp > current.timestamp ? prev : current,
  );

  // Retrieve the hash related to the most recent timestamp
  return mostRecent.hash;
}
