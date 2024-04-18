import { Badge } from "@risc0/ui/badge";
import { buttonVariants } from "@risc0/ui/button";
import { CardDescription, CardFooter, CardHeader, CardTitle } from "@risc0/ui/card";
import type { Metadata } from "next";
import Image from "next/image";
import Link from "next/link";

export const metadata: Metadata = {
  title: "Page Not Found",
};

export default function NotFoundPage() {
  return (
    <div className="container flex min-h-screen max-w-screen-lg flex-col items-center gap-6 py-12 lg:flex-row lg:items-center lg:pt-0">
      <div className="lg:w-1/2">
        <CardHeader className="space-y-1">
          <Badge variant="secondary" className="mb-2 self-start">
            404 Error
          </Badge>
          <CardTitle className="text-2xl">Page Not Found</CardTitle>
          <CardDescription>Sorry, the page you are looking for doesn't exist</CardDescription>
        </CardHeader>

        <CardFooter>
          <Link href="/" className={buttonVariants({ variant: "default" })}>
            Take Me Home
          </Link>
        </CardFooter>
      </div>

      <Image className="lg:mx-auto lg:w-1/2" width="480" height="480" src="/404.svg" alt="Page Not Found" priority />
    </div>
  );
}
