// These are the versions of the app that are available to view in the version picker
// the one marked as latest will be the one that is shown when the user navigates to `/` by default
// you should only have a single version marked as latest
export const VERSIONS = [
  {
    label: "next",
    value: "main", // value is the branch name on github
  },
  {
    label: "release-0.21",
    value: "release-0.21", // value is the branch name on github
    latest: true,
  },
];

const latestVersionsCount = VERSIONS.filter((version) => version.latest).length;

if (latestVersionsCount !== 1) {
  throw new Error("Exactly one version should be marked as the latest");
}

export const latestVersion = VERSIONS.find((version) => version.latest)?.value; // e.g. "release-0.21"
