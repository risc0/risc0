import { NextResponse } from "next/server";

export function GET() {
  return NextResponse.redirect(new URL("/404", "https://risczero.com"), { status: 301 });
}
