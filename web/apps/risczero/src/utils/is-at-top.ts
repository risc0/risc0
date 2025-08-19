export function isAtTop(element): undefined | boolean {
  if (!element) {
    return;
  }

  const rect = element.getBoundingClientRect();

  return rect.top <= 0;
}
