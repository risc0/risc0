import { Subtitle } from "@/app/_components/subtitle";
import NumberTicker from "@/components/number-ticker";

function NumberTickerWrapper({ children, title, subtitle }) {
  return (
    <div className="flex flex-col gap-4 px-6 text-center">
      <h3 className="font-bold text-7xl text-primary lg:text-9xl dark:text-newspaper">{children}</h3>
      <h3 className="mb-3 font-bold text-2xl">{title}</h3>
      <Subtitle className="mx-auto max-w-72">{subtitle}</Subtitle>
    </div>
  );
}

export function OurNumbers() {
  return (
    <section id="our-numbers" className="container max-w-screen-2xl pt-24 pb-48">
      <div className="grid grid-cols-1 gap-y-20 divide-dashed divide-neutral-600 md:grid-cols-3 md:divide-x">
        <NumberTickerWrapper title="Compatible Rust Crates" subtitle="Leverage existing Rust crates to prototype fast.">
          <NumberTicker values={[70, 31]} />%<span className="text-3xl">+</span>
        </NumberTickerWrapper>

        <NumberTickerWrapper title="Gas Savings" subtitle="Dramatically reduce gas fees through off-chain execution.">
          <NumberTicker values={[90, 51]} />%<span className="text-3xl">+</span>
        </NumberTickerWrapper>

        <NumberTickerWrapper
          title="Faster ZK Development"
          subtitle="Significantly accelerate the ZK development cycle."
        >
          <NumberTicker values={[1000, 555]} />
          <span className="text-3xl">x</span>
        </NumberTickerWrapper>
      </div>
    </section>
  );
}
