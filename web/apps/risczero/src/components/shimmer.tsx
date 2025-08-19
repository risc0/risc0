export function Shimmer(w: number, h: number) {
  return `
<svg width="${String(w)}" height="${String(h)}" version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
  <defs>
    <linearGradient id="g">
      <stop stop-color="#333" offset="20%" />
      <stop stop-color="#222" offset="50%" />
      <stop stop-color="#333" offset="70%" />
    </linearGradient>
  </defs>
  <rect width="${String(w)}" height="${String(h)}" fill="#333" />
  <rect id="r" width="${String(w)}" height="${String(h)}" fill="url(#g)" />
  <animate xlink:href="#r" attributeName="x" from="-${String(w)}" to="${String(w)}" dur="1s" repeatCount="indefinite"  />
</svg>`;
}
