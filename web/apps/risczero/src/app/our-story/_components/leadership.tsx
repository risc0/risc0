import { Title } from "@/app/_components/title";
import { Shimmer } from "@/components/shimmer";
import { getAllLeadership } from "@/libs/notion/get-all-leadership";
import { toBase64 } from "@/utils/to-base-64";
import Image from "next/image";
import Link from "next/link";
import { RiLinkedinFill, RiTwitterXLine } from "react-icons/ri";

export async function Leadership() {
  const leadership = await getAllLeadership();

  if (!leadership) {
    return null;
  }

  return (
    <section id="leadership" className="py-12 md:py-24">
      <Title className="mb-12 text-center md:text-left">Leadership</Title>

      <div className="grid grid-cols-1 gap-4 gap-y-16 lg:grid-cols-5">
        {leadership.map((leader) => (
          <div className="flex flex-col items-center justify-center" key={leader.id}>
            <Link href={leader.linkedin ?? leader.twitter ?? ""} target="_blank">
              <Image
                unoptimized
                src={leader.pageCover}
                alt={leader.title ?? ""}
                width={180}
                height={180}
                placeholder={`data:image/svg+xml;base64,${toBase64(Shimmer(180, 180))}`}
                loading="lazy"
                draggable={false}
                className="mb-6 rounded-full border-2 border-border object-cover saturate-0 transition-all hover:shadow-xl hover:saturate-100 dark:hover:border-[hsl(var(--primary))] dark:hover:shadow-[0_0_18px_2px_hsl(var(--primary))]"
              />
            </Link>

            <h3 className="font-bold text-primary text-xl">{leader.title}</h3>
            <h4 className="text-lg">{leader.slug}</h4>

            <div className="flex flex-row items-center gap-4">
              {leader.twitter && (
                <Link target="_blank" href={leader.twitter} className="mt-2">
                  <RiTwitterXLine size={17} />
                </Link>
              )}

              {leader.linkedin && (
                <Link target="_blank" href={leader.linkedin} className="mt-2">
                  <RiLinkedinFill size={22} />
                </Link>
              )}
            </div>
          </div>
        ))}
      </div>
    </section>
  );
}
