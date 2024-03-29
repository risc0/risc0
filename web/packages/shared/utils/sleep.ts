// Helpful function to sleep for a given amount of time
export default function sleep(ms: number) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}
