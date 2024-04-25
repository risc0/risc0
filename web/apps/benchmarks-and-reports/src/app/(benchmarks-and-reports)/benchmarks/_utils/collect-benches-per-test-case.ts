type DataSetEntry = {
  date: number;
  tool: string;
  commit: {
    author: {
      email: string;
      name: string;
      username: string;
    };
    committer: {
      email: string;
      name: string;
      username: string;
    };
    distinct: boolean;
    id: string;
    message: string;
    timestamp: string;
    tree_id: string;
    url: string;
  };
  benches: { name: string; range: string; unit: string; value: number }[];
};

export type FormattedDataSetEntry = Omit<DataSetEntry, "benches"> & {
  bench: {
    name: string;
    range: string;
    unit: string;
    value: number;
  };
};

export function collectBenchesPerTestCase(entries: DataSetEntry[]): Map<string, FormattedDataSetEntry[]> {
  const map = new Map();

  for (const entry of entries) {
    const { commit, date, tool, benches } = entry;

    for (const bench of benches) {
      const result = { commit, date, tool, bench };
      const arr = map.get(bench.name);

      if (arr === undefined) {
        map.set(bench.name, [result]);
      } else {
        arr.push(result);
      }
    }
  }

  return map;
}
