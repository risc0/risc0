import type { Metadata } from "next";

export const metadata: Metadata = {
  title: "App is in Maintenance",
};

export default function MaintenancePage() {
  return (
    <div className="container grid min-h-screen items-center">
      <div className="flex flex-col space-y-2 text-center">
        <h1 className="title-sm">Benchmarks & Reports Is Currently in Maintenance</h1>
        <p className="text-balance text-muted-foreground text-sm">Come again soon 👋</p>
      </div>
    </div>
  );
}
