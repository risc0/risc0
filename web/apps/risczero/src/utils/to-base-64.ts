export function toBase64(str: string) {
  return typeof window === "undefined" ? Buffer.from(str).toString("base64") : window.btoa(str);
}
