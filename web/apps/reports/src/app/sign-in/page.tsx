import type { Metadata } from "next";
import { cookies } from "next/headers";
import Image from "next/image";
import { redirect } from "next/navigation";
import Script from "next/script";
import SignInFooter from "./_components/sign-in-footer";
import SignInHeader from "./_components/sign-in-header";

export const metadata: Metadata = {
  title: "Sign In",
};

export default function SignInPage() {
  const cookieStore = cookies();
  const token = cookieStore.get("auth_token");

  if (token) {
    redirect("/reports");
  }

  return (
    <div className="relative flex min-h-dvh items-stretch justify-center overflow-y-hidden bg-slate-200 dark:bg-slate-700">
      <div className="z-20 mx-auto w-full bg-background px-8 py-6 shadow-2xl md:my-12 md:max-w-screen-sm md:rounded-3xl md:px-12 md:py-10">
        <div className="flex h-full flex-col justify-between">
          <SignInHeader />

          <div className="flex flex-col justify-center space-y-6">
            <div className="relative flex flex-col text-center">
              <div className="absolute top-[25%] hidden translate-y-[-50%] opacity-50 dark:block">
                <Image
                  className="pointer-events-none animate-fade-in-up select-none"
                  src="/sign-in.svg"
                  alt="Sign in"
                  width={1000}
                  height={1000}
                  priority
                />
              </div>

              <h1 className="title-sm mb-4">Sign In</h1>

              <div className="flex h-10 justify-center align-middle">
                <Script src="https://accounts.google.com/gsi/client" async defer />

                <div
                  id="g_id_onload"
                  data-client_id="480626743391-kger22jsjnkmm00cl3ie7getnoh7rjlg.apps.googleusercontent.com"
                  data-context="signin"
                  data-ux_mode="popup"
                  data-callback="doLogin"
                  data-itp_support="true"
                />
                <div
                  className="g_id_signin"
                  data-type="standard"
                  data-shape="pill"
                  data-theme="filled_black"
                  data-text="continue_with"
                  data-size="large"
                  data-width="280"
                  data-logo_alignment="left"
                />
              </div>
            </div>
          </div>

          <SignInFooter />
        </div>
      </div>
    </div>
  );
}
