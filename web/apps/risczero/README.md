# RISC Zero Website

This repository contains the source code for the [RISC Zero website](https://www.risczero.com/).

## Features

- Modern web development with Next.js and TypeScript
- Responsive design using Tailwind CSS
- Dynamic content management with Notion API integration
- Dark mode support
- SEO optimization with dynamic OG image generation

## Getting Started

### Prerequisites

- Node.js (v20)
- [bun](https://bun.sh/)

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/risc0/risc0-website.git
   cd risc0-website
   ```

2. Install dependencies:
   ```bash
   bun install
   ```

3. Set up environment variables:
   Create a `.env.local` file in the root directory and add the following variables:

   ```bash
   NOTION_TOKEN=your_notion_token
   NOTION_ACTIVE_USER=your_notion_user_id
   ```

   Refer to the `src/env.ts` file for more details on environment variables.

### Development

Run the development server:

```bash
bun run dev
```
