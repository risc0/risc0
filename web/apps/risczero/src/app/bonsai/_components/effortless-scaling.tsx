import Image from "next/image";
import { Subtitle } from "@/app/_components/subtitle";
import { Title } from "@/app/_components/title";

const FEATURES = [
  {
    name: "Parallel Proving",
    icon: "/icons/parallel.svg",
    description:
      "Utilize a parallelized cluster for rapid proving times, freeing you to focus on building your application.",
  },
  {
    name: "99.9% Uptime",
    icon: "/icons/uptime.svg",
    description: "Rely on our robust infrastructure for consistent, uninterrupted service you can count on.",
  },
  {
    name: "Simple Deployment",
    icon: "/icons/deploy.svg",
    description: "Integrate seamlessly with your existing systems using our user-friendly APIs and documentation.",
  },
  {
    name: "Enterprise-grade Security",
    icon: "/icons/security.svg",
    description:
      "Rigorously audited and battle-tested by industry leaders, ensuring robust protection for your operations.",
  },
  {
    name: "Dedicated ZK Team",
    icon: "/icons/team.svg",
    description: "Access specialized ZK experts for seamless implementation and ongoing maintenance support.",
  },
  {
    name: "Auto-scaling",
    icon: "/icons/scaling.svg",
    description:
      "Dynamically adjust resources to match your demand, ensuring optimal performance as your needs fluctuate.",
  },
] as const;

export function EffortlessScaling() {
  return (
    <div className="container max-w-screen-2xl">
      <Title className="mx-auto mb-0 max-w-screen-sm py-12 text-center md:py-24">
        Effortless Scaling for All Your Proving Needs
      </Title>

      <div className="mb-36 grid grid-cols-1 gap-24 md:grid-cols-3">
        {FEATURES.map(({ name, description, icon }) => (
          <div key={name} className="flex flex-col gap-3">
            <div className="flex items-center gap-6">
              <Image
                src={icon}
                alt={name}
                draggable={false}
                width={32}
                height={32}
                unoptimized
                loading="lazy"
                className="size-[32px] object-contain object-center dark:invert"
              />
              <Title as="h3" className="mb-0 text-2xl md:text-2xl">
                {name}
              </Title>
            </div>
            <Subtitle className="md:text-lg">{description}</Subtitle>
          </div>
        ))}
      </div>
    </div>
  );
}
