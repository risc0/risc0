import Link from "next/link";

export default function SignInFooter() {
  return (
    <div className="space-x-2 text-center text-muted-foreground text-xs">
      <span>
        Built by{" "}
        <Link href="https://www.risczero.com" target="_blank">
          Risc Zero
        </Link>
      </span>
      <span>•</span>
      <span>Version: {process.env.NEXT_PUBLIC_APP_VERSION}</span>
    </div>
  );
}
