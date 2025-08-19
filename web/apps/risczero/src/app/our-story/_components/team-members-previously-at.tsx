import { Card, CardHeader, CardTitle } from "@risc0/ui/card";
import { Title } from "@/app/_components/title";

export function TeamMembersPreviouslyAt() {
  return (
    <div className="py-12 md:py-24">
      <Title className="mb-12 text-center md:text-left">Made up of Team Members Previously At</Title>

      <div className="grid grid-cols-2 gap-8 sm:grid-cols-3 md:grid-cols-4 xl:grid-cols-6">
        {[
          "Amazon",
          "Chainsafe",
          "Coinbase",
          "Google",
          "Intel",
          "Meta",
          "Microsoft",
          "Mina Foundation",
          "O(1) Labs",
          "Ripple",
          "SoFi",
          "Uber",
        ].map((company) => (
          <Card
            key={company}
            className="outline-dashed outline-1 outline-neutral-200 outline-offset-8 dark:outline-neutral-700"
          >
            <CardHeader className="py-12">
              <CardTitle className="truncate text-center">{company}</CardTitle>
            </CardHeader>
          </Card>
        ))}
      </div>
    </div>
  );
}
