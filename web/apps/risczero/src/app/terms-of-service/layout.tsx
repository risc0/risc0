import { Title } from "../_components/title";

export default function TermsOfServiceLayout({ children }) {
  return (
    <div className="container max-w-screen-lg py-12 md:py-24">
      <Title as="h1">Terms of Service</Title>

      <div className="relative w-full flex-none">{children}</div>
    </div>
  );
}
