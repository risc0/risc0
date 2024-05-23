import "server-only";

export async function fetchDatasheet({ version, url }: { version: string; url: string }) {
  return fetch(`https://raw.githubusercontent.com/risc0/ghpages/${version}/dev/datasheet/${url}`, {
    headers: {
      Accept: "application/vnd.github.v3.raw",
    },
    cache: "no-store",
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
