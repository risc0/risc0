import type { Version } from "@/types/version";
import { create } from "zustand";
import { persist } from "zustand/middleware";

type VersionStore = {
	version: Version | undefined;
	setVersion: (version: Version | undefined) => void;
};

export const useVersion = create<VersionStore>()(
	persist(
		(set) => ({
			version: undefined,
			setVersion: (version) => set({ version }),
		}),
		{ name: "version" },
	),
);
