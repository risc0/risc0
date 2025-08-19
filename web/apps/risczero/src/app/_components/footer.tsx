import { ProgressBarLink } from "@/components/progress-bar-link";
import { EmailSignup } from "./email-signup";
import { HeaderLogo } from "./header-logo";

const FOOTER_LINKS_1 = [
  {
    title: "GitHub",
    url: "https://github.com/risc0",
  },
  {
    title: "Discord",
    url: "https://discord.com/invite/risczero",
  },
  {
    title: "X",
    url: "https://x.com/RiscZero",
  },
  {
    title: "YouTube",
    url: "https://www.youtube.com/@risczero",
  },
] as const;

const FOOTER_LINKS_2 = [
  /*{
    title: "Careers",
    url: "https://jobs.ashbyhq.com/RiscZero",
  },*/
  {
    title: "Developers",
    url: "https://dev.risczero.com",
  },
  {
    title: "Bug Bounties",
    url: "https://hackenproof.com/company/risc-zero/programs",
  },
  {
    title: "Privacy Policy",
    url: "/privacy-policy",
  },
  {
    title: "Terms of Service",
    url: "/terms-of-service",
  },
] as const;

export function Footer() {
  return (
    <footer className="mt-48 bg-[#E5E3D5] py-28 text-neutral-800">
      <div className="container max-w-screen-2xl">
        <div className="flex max-w-screen-xl flex-col justify-between gap-12 md:flex-row">
          <div className="flex flex-1 flex-col justify-between gap-8">
            <EmailSignup />

            <HeaderLogo className="hidden md:block dark:invert-0" />
          </div>

          <div className="flex flex-1 flex-col items-start md:items-end">
            <div className="grid grid-cols-2 gap-12 lg:gap-24">
              <ul className="space-y-2">
                {FOOTER_LINKS_1.map(({ url, title }) => (
                  <li key={title}>
                    <ProgressBarLink
                      className="subtitle-sm link font-mono text-inherit dark:text-inherit"
                      href={url}
                      target="_blank"
                    >
                      {title}
                    </ProgressBarLink>
                  </li>
                ))}
              </ul>

              <ul className="space-y-2">
                {FOOTER_LINKS_2.map(({ url, title }) => {
                  return (
                    <li key={title}>
                      <ProgressBarLink
                        className="subtitle-sm link font-mono text-inherit dark:text-inherit"
                        href={url}
                        target="_blank"
                      >
                        {title}
                      </ProgressBarLink>
                    </li>
                  );
                })}
              </ul>
            </div>
          </div>
        </div>
      </div>
    </footer>
  );
}
