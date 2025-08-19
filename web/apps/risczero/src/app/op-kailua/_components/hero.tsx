import { Button } from "@risc0/ui/button";
import { ArrowUpRightIcon } from "lucide-react";
import Image from "next/image";
import Link from "next/link";
import { Title } from "@/app/_components/title";
import { BoxReveal } from "@/components/box-reveal";
import { OpKailua3dCard } from "./op-kailua-3d-card";

export function Hero() {
  return (
    <section
      id="hero"
      className="container flex min-h-[56dvh] max-w-screen-2xl flex-col items-center justify-between gap-x-24 gap-y-12 md:flex-row"
    >
      <div className="size-full max-w-[38rem] items-center justify-center overflow-hidden pt-8">
        <BoxReveal duration={0.3} theme="op-kailua">
          <Title as="h1" className="mb-0 py-3 text-5xl md:text-7xl">
            <Image
              className="dark:invert"
              unoptimized
              src="/solutions/op-kailua.svg"
              alt="OP Kailua Logo"
              width={740}
              height={87.55}
            />
          </Title>
        </BoxReveal>

        <BoxReveal duration={0.3} theme="op-kailua">
          <p className="text-2xl">
            Future-proof your OP Chain with ZK. Choose between ZK Fraud or Validity Proofs for faster finality and
            stronger security.
          </p>
        </BoxReveal>

        <div className="mt-10">
          <BoxReveal duration={0.3} theme="op-kailua">
            <div className="flex flex-col gap-4 md:flex-row">
              <Link tabIndex={-1} href="https://github.com/risc0/kailua" target="_blank">
                <Button
                  size="lg"
                  className="bg-op-kailua-light text-default-dark dark:bg-op-kailua-dark dark:text-default-light"
                >
                  Get Started
                </Button>
              </Link>
              <Link
                tabIndex={-1}
                href="https://docs.google.com/forms/d/e/1FAIpQLScH3mRdi8pCeaunup7vtX7Ack9AaMUKY54TD3y8aj131WgK1g/viewform"
                target="_blank"
              >
                <Button size="lg" variant="secondary" endIcon={<ArrowUpRightIcon />}>
                  Get in Touch
                </Button>
              </Link>
            </div>
          </BoxReveal>
        </div>
      </div>

      <div className="animate-fade-in-left duration-300">
        <OpKailua3dCard />
      </div>
    </section>
  );
}
