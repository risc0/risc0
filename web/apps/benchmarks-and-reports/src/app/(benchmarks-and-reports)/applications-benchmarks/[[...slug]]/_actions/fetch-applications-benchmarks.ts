"use server";

export async function fetchApplicationsBenchmarks(url: string) {
  return fetch(`https://risc0.github.io/ghpages/dev/benchmarks/${url}`)
    .then((response) => {
      if (!response.ok) {
        throw new Error(`Error fetching ${url}: ${response.statusText}`);
      }

      return response.text();
    })
    .catch((error) => {
      console.error(`Failed fetching ${url}:`, error.message);

      return undefined; // Handle individual failures gracefully
    });
}
