import { parseConnectionString } from "@vercel/edge-config";
import { type NextRequest, NextResponse } from "next/server";
import { getFeatureFlag } from "./get-feature-flag";

export const config = {
  matcher: [
    /*
     * Match all request paths except for the ones starting with:
     * - api (API routes)
     * - _next/static (static files)
     * - _next/image (image optimization files)
     * - favicon.png (favicon)
     * - fonts (fonts)
     * - maintenance (maintenance page)
     */
    "/((?!api|_next/static|_next/image|favicon.png|fonts|maintenance).*)",
  ],
};

export default async (request: NextRequest) => {
  // for demo purposes, warn when there is no EDGE_CONFIG
  if (!process.env.EDGE_CONFIG || !parseConnectionString(process.env.EDGE_CONFIG)) {
    console.error("Error: Please set the EDGE_CONFIG environment variable in the Vercel project settings");

    return;
  }

  const maintenanceFeatureFlag = await getFeatureFlag("maintenance");

  try {
    // if the global maintenance flag is enabled, redirect to the maintenance page
    if (maintenanceFeatureFlag) {
      request.nextUrl.pathname = "/maintenance";

      return NextResponse.redirect(request.nextUrl);
    }
  } catch (error) {
    console.error(error);
  }
};
