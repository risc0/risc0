import { Card, CardContent, CardFooter, CardHeader, CardTitle } from "@risc0/ui/card";
import Image from "next/image";
import Link from "next/link";

export function WhatMakesUs() {
  return (
    <div className="grid grid-cols-1 gap-4 py-12 md:py-24 lg:grid-cols-3">
      <Card className="flex min-h-72 animate-fade-in-up flex-col fill-mode-forwards text-default-light opacity-0 delay-0 duration-300 dark:bg-newspaper">
        <CardHeader className="space-y-0 p-8">
          <CardTitle className="text-3xl">How We Started</CardTitle>
        </CardHeader>

        <CardContent className="px-8 py-0">
          <Image
            src="/ascii/how-we-started.png"
            unoptimized
            alt="How We Started"
            width={408}
            priority
            draggable={false}
            height={192}
            className="mx-auto h-48 object-contain object-center"
          />
        </CardContent>

        <CardFooter className="p-8 text-xl">
          RISC Zero was started in 2021 to tackle the biggest challenge to our industry, and potentially our society —
          increased centralization and consolidation of not just the applications we use but the infrastructure we use
          to build and manage them.
        </CardFooter>
      </Card>

      <Card className="flex min-h-72 animate-fade-in-up flex-col fill-mode-forwards text-default-light opacity-0 delay-75 duration-300 dark:bg-newspaper">
        <CardHeader className="space-y-0 p-8">
          <CardTitle className="text-3xl">Our Purpose</CardTitle>
        </CardHeader>

        <CardContent className="px-8 py-0">
          <Image
            src="/ascii/our-purpose.png"
            unoptimized
            alt="Our Purpose"
            width={408}
            draggable={false}
            priority
            height={192}
            className="mx-auto h-48 object-contain object-center"
          />
        </CardContent>

        <CardFooter className="p-8 text-xl">
          RISC Zero is bringing general-purpose computing to the zero-knowledge ecosystem — enabling users to trust
          programs run anywhere while allowing developers to use the tools they already know and love.
        </CardFooter>
      </Card>

      <Card className="flex min-h-72 animate-fade-in-up flex-col fill-mode-forwards text-default-light opacity-0 delay-150 duration-300 dark:bg-newspaper">
        <CardHeader className="space-y-0 p-8">
          <CardTitle className="text-3xl">What We Do</CardTitle>
        </CardHeader>

        <CardContent className="px-8 py-0">
          <Image
            src="/ascii/what-we-do.png"
            unoptimized
            priority
            alt="What We Do"
            draggable={false}
            width={408}
            height={192}
            className="mx-auto h-48 object-contain object-center"
          />
        </CardContent>

        <CardFooter className="block p-8 text-xl">
          We're a diverse group of hackers, futurists, and nerds dedicated to making the internet the place we all
          deserve. We've already built the world's first zkVM capable of running arbitrary code as a zero-knowledge
          proof. We're now building an ecosystem on top of it.{" "}
          <Link href="https://jobs.ashbyhq.com/RiscZero" target="_blank" className="link !text-default-light underline">
            Join us
          </Link>
          .
        </CardFooter>
      </Card>
    </div>
  );
}
