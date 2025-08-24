/**
 * Type guard to check if a value is null or undefined
 * @param val - The value to check
 * @returns True if the value is null or undefined, false otherwise
 */
export function isNil(val: unknown): boolean {
  return val == null;
}

/**
 * Type guard to check if a value is not null or undefined
 * @param val - The value to check
 * @returns True if the value is not null or undefined, false otherwise
 */
export function isNotNil<T>(val: T | null | undefined): val is T {
  return !isNil(val);
}
