import { Subtitle } from "@/app/_components/subtitle";
import { Title } from "@/app/_components/title";

const KEY_POINTS = [
  {
    title: "Seamless Integration",
    subtitle: "Execute Solidity contracts directly within the zkVM. No new languages or architectures to learn.",
  },
  {
    title: "Boundless Computation",
    subtitle:
      "Bypass transaction size and block limits. Implement sophisticated on-chain logic previously impossible on Ethereum.",
  },
  {
    title: "Reduced Gas",
    subtitle: "Reduce gas costs by up to 90% through verifiable off-chain execution.",
  },
] as const;

export function KeyPoints() {
  return (
    <section id="key-points" className="container max-w-screen-2xl py-12 md:py-24">
      <div className="grid grid-cols-3 gap-32">
        <div className="col-span-2">
          <div className="relative block size-full">test</div>
        </div>
        <div className="col-span-1 space-y-14">
          {KEY_POINTS.map(({ title, subtitle }) => (
            <div key={title}>
              <div className="mb-4 size-8 rounded-full bg-steel-light dark:bg-steel-dark" />
              <Title className="mb-3 text-2xl md:text-2xl">{title}</Title>
              <Subtitle className="md:text-lg">{subtitle}</Subtitle>
            </div>
          ))}
        </div>
      </div>
    </section>
  );
}
