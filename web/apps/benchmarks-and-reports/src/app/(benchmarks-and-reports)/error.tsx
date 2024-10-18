"use client"; // Error components must be Client components

import { ErrorMessage, type ErrorMessageProps } from "shared/client/components/error-message";

export default function BenchmarksAndReportsError({ ...rest }: ErrorMessageProps) {
  return <ErrorMessage {...rest} />;
}
