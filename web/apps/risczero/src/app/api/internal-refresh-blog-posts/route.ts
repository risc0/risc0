import { revalidatePath } from "next/cache";
import { NextResponse } from "next/server";

export function GET() {
  revalidatePath("/blog", "layout");

  return NextResponse.json({
    success: true,
  });
}
