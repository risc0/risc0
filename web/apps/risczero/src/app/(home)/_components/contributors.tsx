import { Marquee } from "@/components/marquee";
import { Avatar, AvatarFallback } from "@risc0/ui/avatar";
import { shuffle } from "es-toolkit";
import Image from "next/image";
import Link from "next/link";
import { getContributors } from "../_actions/get-contributors";

export async function Contributors() {
  const { data: contributors } = await getContributors();

  if (!contributors) {
    return null;
  }

  const shuffledContributors = shuffle(contributors);
  const firstRow = shuffledContributors.slice(0, shuffledContributors.length / 2);
  const secondRow = shuffledContributors.slice(shuffledContributors.length / 2);

  return (
    <>
      <Marquee pauseOnHover className="animate-fade-in [--duration:30s]">
        {firstRow.map((contributor) => (
          <Link
            tabIndex={-1}
            title={contributor.login}
            href={contributor.html_url}
            key={contributor.id}
            target="_blank"
            className="grayscale transition-all hover:grayscale-0"
          >
            <Avatar className="size-16 shadow-md">
              <Image
                src={contributor.avatar_url}
                alt={contributor.login}
                loading="lazy"
                width={64}
                height={64}
                quality={75}
                draggable={false}
                className="aspect-auto object-cover object-center"
              />
              <AvatarFallback>{contributor.login[0]}</AvatarFallback>
            </Avatar>
          </Link>
        ))}
      </Marquee>
      <Marquee pauseOnHover reverse className="animate-fade-in [--duration:30s]">
        {secondRow.map((contributor) => (
          <Link
            tabIndex={-1}
            title={contributor.login}
            href={contributor.html_url}
            key={contributor.id}
            target="_blank"
            className="grayscale transition-all hover:grayscale-0"
          >
            <Avatar className="size-16 shadow-md">
              <Image
                src={contributor.avatar_url}
                alt={contributor.login}
                loading="lazy"
                width={64}
                height={64}
                draggable={false}
                className="aspect-auto object-cover object-center"
              />
              <AvatarFallback>{contributor.login[0]}</AvatarFallback>
            </Avatar>
          </Link>
        ))}
      </Marquee>
    </>
  );
}
