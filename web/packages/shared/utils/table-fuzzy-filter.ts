import { rankItem } from "@tanstack/match-sorter-utils";
import type { FilterFn } from "@tanstack/react-table";

// Generic type for table data rows
export const tableFuzzyFilter = <TData extends Record<string, unknown>>(
  row: { getValue: (columnId: string) => unknown },
  columnId: string,
  value: string,
  addMeta: (meta: { itemRank: number }) => void
): boolean => {
  // Rank the item
  const itemRank = rankItem(row.getValue(columnId), value);

  // Store the itemRank info
  addMeta({
    itemRank,
  });

  // Return if the item should be filtered in/out
  return itemRank.passed;
};
