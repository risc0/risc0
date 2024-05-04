import { Button } from "@risc0/ui/button";
import { Select, SelectContent, SelectItem, SelectTrigger, SelectValue } from "@risc0/ui/select";
import type { Table } from "@tanstack/react-table";
import { ChevronLeftIcon, ChevronRightIcon, ChevronsLeftIcon, ChevronsRightIcon } from "lucide-react";

export function TablePagination<TData>({ table }: { table: Table<TData> }) {
  return (
    <div className="flex items-center justify-between space-x-6 lg:space-x-8">
      <div className="flex items-center space-x-2">
        <p className="font-medium text-sm">Rows per page</p>
        <Select
          value={`${table.getState().pagination.pageSize}`}
          onValueChange={(value) => {
            table.setPageSize(Number(value));
          }}
        >
          <SelectTrigger className="h-8 w-[92px]">
            <SelectValue placeholder={table.getState().pagination.pageSize} />
          </SelectTrigger>
          <SelectContent side="top">
            {[100, 250, 500, 1000].map((pageSize) => (
              <SelectItem className="cursor-pointer" key={pageSize} value={`${pageSize}`}>
                {pageSize}
              </SelectItem>
            ))}
          </SelectContent>
        </Select>
      </div>

      <div className="flex flex-row justify-end">
        <div className="flex w-[100px] items-center font-medium text-sm">
          Page {table.getState().pagination.pageIndex + 1} of {table.getPageCount()}
        </div>
        <div className="flex items-center space-x-2">
          <Button
            variant="outline"
            className="hidden h-8 w-8 p-0 lg:flex"
            onClick={() => table.setPageIndex(0)}
            disabled={!table.getCanPreviousPage()}
            size="icon"
            startIcon={<ChevronsLeftIcon />}
          >
            <span className="sr-only">Go to first page</span>
          </Button>
          <Button
            variant="outline"
            className="h-8 w-8 p-0"
            onClick={() => table.previousPage()}
            disabled={!table.getCanPreviousPage()}
            size="icon"
            startIcon={<ChevronLeftIcon />}
          >
            <span className="sr-only">Go to previous page</span>
          </Button>
          <Button
            variant="outline"
            className="h-8 w-8 p-0"
            onClick={() => table.nextPage()}
            disabled={!table.getCanNextPage()}
            size="icon"
            startIcon={<ChevronRightIcon />}
          >
            <span className="sr-only">Go to next page</span>
          </Button>
          <Button
            variant="outline"
            className="hidden h-8 w-8 p-0 lg:flex"
            onClick={() => table.setPageIndex(table.getPageCount() - 1)}
            disabled={!table.getCanNextPage()}
            size="icon"
            startIcon={<ChevronsRightIcon />}
          >
            <span className="sr-only">Go to last page</span>
          </Button>
        </div>
      </div>
    </div>
  );
}
