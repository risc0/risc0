import { Button } from "@risc0/ui/button";
import { Card, CardContent, CardHeader, CardTitle } from "@risc0/ui/card";
import Link from "next/link";
import { Subtitle } from "@/app/_components/subtitle";
import { Title } from "@/app/_components/title";

export function UpgradeAtYourOwnPace() {
  return (
    <div className="container mt-48 max-w-screen-2xl">
      <Title className="mb-6 md:text-5xl">Upgrade At Your Own Pace</Title>
      <Subtitle>ZK security, on your terms.</Subtitle>

      <div className="mt-8 grid grid-cols-1 gap-6 md:grid-cols-3">
        <Card className="flex flex-col justify-between">
          <CardHeader className="p-8 pt-10">
            <CardTitle className="max-w-72 text-5xl">Risk-Free Testing</CardTitle>
          </CardHeader>
          <CardContent className="p-8 pb-10">
            Integrate OP Kailua without enabling withdrawals to test performance in a production-like environment.
          </CardContent>
        </Card>

        <Card className="flex flex-col justify-between">
          <CardHeader className="p-8 pt-10">
            <CardTitle className="max-w-72 text-5xl">Incremental Adoption</CardTitle>
          </CardHeader>
          <CardContent className="p-8 pb-10">
            Submit validity proofs for only a portion of sequencing proposals before fully transitioning.
          </CardContent>
        </Card>

        <Card className="flex flex-col justify-between">
          <CardHeader className="p-8 pt-10">
            <CardTitle className="max-w-72 text-5xl">Adaptive Security</CardTitle>
          </CardHeader>
          <CardContent className="p-8 pb-10">
            Switch freely between Hybrid mode and Validity mode based on your rollup's needs.
          </CardContent>
        </Card>
      </div>

      <div className="mt-16 flex justify-center">
        <Link
          href="https://docs.google.com/forms/d/e/1FAIpQLScH3mRdi8pCeaunup7vtX7Ack9AaMUKY54TD3y8aj131WgK1g/viewform"
          target="_blank"
          tabIndex={-1}
        >
          <Button
            size="lg"
            className="bg-op-kailua-light text-default-dark dark:bg-op-kailua-dark dark:text-default-light"
          >
            Schedule a Demo
          </Button>
        </Link>
      </div>
    </div>
  );
}
