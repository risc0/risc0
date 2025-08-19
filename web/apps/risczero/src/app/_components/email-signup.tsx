"use client";

import { Button } from "@risc0/ui/button";
import { Input } from "@risc0/ui/input";
import type { FormEvent } from "react";

async function handleSubmit(event: FormEvent<HTMLFormElement>) {
  event.preventDefault();

  const form = event.target as HTMLFormElement;
  const formData = new FormData(form);

  try {
    const response = await fetch(form.action, {
      method: "POST",
      body: formData,
    });

    if (response.ok) {
      alert("You are now signed up for email updates!");
      form.reset(); // Clear the form
    } else {
      alert("Sign up failed.");
    }
  } catch (error) {
    console.error(error);
    alert("An error occurred.");
  }
}

export function EmailSignup() {
  return (
    <div className="w-full max-w-xs">
      <p className="subtitle-sm mb-3">Sign up for updates</p>

      <form
        name="Form"
        method="POST"
        action="https://hubspotonwebflow.com/api/forms/a9a07523-0b40-4f38-b02f-5dc81a7eb3da"
        encType="multipart/form-data"
        data-name="General Email List - New Web Footer"
        data-wf-hs-form="webflowHubSpotForm"
        data-wf-page-id="65c266cf5b862254c5a291d5"
        data-wf-element-id="7b66eefd-4d30-2458-570b-a70887c85766"
        className="flex flex-row items-start gap-2"
        onSubmit={async (event) => {
          await handleSubmit(event);
        }}
      >
        <input type="hidden" name="hutk" />
        <input type="hidden" name="ipAddress" />
        <input type="hidden" name="pageUri" />
        <input type="hidden" name="pageId" />
        <input type="hidden" name="pageName" />

        <Input
          type="email"
          required
          name="email"
          id="email"
          wrapperClassName="w-full max-w-xs"
          placeholder="Your Email"
          className="border-2 bg-newspaper ring-offset-2 focus-visible:ring-black focus-visible:ring-offset-newspaper"
        />

        <Button variant="secondary" type="submit">
          Sign Up
        </Button>
      </form>
    </div>
  );
}
