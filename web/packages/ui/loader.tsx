import Image from "next/image";

export default function Loader() {
  return (
    <div className="mx-auto flex animate-fade-in-up flex-col items-center justify-center gap-3">
      <Image unoptimized height={120} width={128} src="/loading.gif" alt="Loading" />
      <p className="text-sm">Loading…</p>
    </div>
  );
}
