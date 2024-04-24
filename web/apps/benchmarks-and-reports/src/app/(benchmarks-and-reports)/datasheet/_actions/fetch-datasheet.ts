"use server";

export async function fetchDatasheet(url: string) {
  return fetch(`https://risc0.github.io/ghpages/dev/datasheet/${url}`, {
    next: { revalidate: 3600 },
  })
    .then((response) => {
      if (!response.ok) {
        throw new Error(`Error fetching ${url}: ${response.statusText}`);
      }

      return response.json();
    })
    .catch((error) => {
      console.error(`Failed fetching ${url}:`, error.message);

      return null; // Handle individual failures gracefully
    });
}
