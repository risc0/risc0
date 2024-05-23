import "server-only";

export async function fetchDatasheetCommitHash({ version }: { version: string }) {
  const response = await fetch(
    `https://raw.githubusercontent.com/risc0/ghpages/${version}/dev/datasheet/COMMIT_HASH.txt`,
    {
      headers: {
        Accept: "application/vnd.github.v3.raw",
      },
      cache: "no-store",
    },
  );
  const responseText = await response.text();

  return responseText;
}
