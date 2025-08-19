"use client"; // Error components must be Client components

import { Alert, AlertDescription, AlertTitle } from "@risc0/ui/alert";
import { AlertTriangleIcon } from "lucide-react";
import { useEffect } from "react";

export default function RootError({ error }: { error: Error }) {
  useEffect(() => {
    // Log the error to an error reporting service
    console.error(error);
  }, [error]);

  return (
    <div className="container flex max-w-screen-2xl flex-1 items-start justify-start">
      <Alert variant="destructive" className="w-full">
        <AlertTriangleIcon className="size-4" />
        <AlertTitle>Something went wrong, but we're looking into it</AlertTitle>
        <AlertDescription>{String(error.cause ?? error.message ?? error.name ?? "Unknown error")}</AlertDescription>
      </Alert>
    </div>
  );
}
