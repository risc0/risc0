export function HtmlComment({ text }) {
  // biome-ignore lint/security/noDangerouslySetInnerHtml: ignore
  return <span className="hidden" dangerouslySetInnerHTML={{ __html: `<!-- ${text} -->` }} />;
}
