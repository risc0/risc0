// These are the versions of the app that are available to view in the version picker
// the one marked as latest will be the one that is shown when the user navigates to `/` by default
// you should only have a single version marked as latest
export const VERSIONS = [
	{
		label: "next",
		value: "main", // value is the branch name on github
	},
	{
		label: "3.0",
		value: "release-3.0", // value is the branch name on github
	},
	{
		label: "2.0",
		value: "release-2.0", // value is the branch name on github
	},
	{
		label: "1.2",
		value: "release-1.2", // value is the branch name on github
	},
	{
		label: "1.1",
		value: "release-1.1", // value is the branch name on github
	},
	{
		label: "1.0",
		value: "release-1.0", // value is the branch name on github
	},
	{
		label: "0.21",
		value: "release-0.21", // value is the branch name on github
	},
];

export const latestVersion = "release-3.0";
