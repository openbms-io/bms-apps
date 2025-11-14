This is a [Next.js](https://nextjs.org) project bootstrapped with [`create-next-app`](https://nextjs.org/docs/app/api-reference/cli/create-next-app).

## Getting Started

First, run the development server:

```bash
npm run dev
# or
yarn dev
# or
pnpm dev
# or
bun dev
```

Open [http://localhost:3000](http://localhost:3000) with your browser to see the result.

You can start editing the page by modifying `app/page.tsx`. The page auto-updates as you edit the file.

This project uses [`next/font`](https://nextjs.org/docs/app/building-your-application/optimizing/fonts) to automatically optimize and load [Geist](https://vercel.com/font), a new font family for Vercel.

## Building Semantics API Client

The Designer app includes a TypeScript client for the Building Semantics API (ASHRAE 223P integration). The client is auto-generated from the FastAPI OpenAPI specification.

### When to Regenerate

Regenerate the TypeScript client whenever:

- FastAPI Pydantic DTOs change (field names, types, or structure)
- New API endpoints are added
- Existing endpoints are modified or removed
- After pulling changes that modify `apps/building-semantics/src/routers/`

### How to Regenerate

```bash
# 1. Start the FastAPI server (required for OpenAPI spec)
pnpm building-semantics:run

# 2. In a separate terminal, regenerate the client
cd apps/designer
pnpm generate:api-client
```

The generated client will be created at:

```
apps/designer/src/domains/building-semantics/api/generated/
```

### Build Validation

The build process validates:

- ✅ TypeScript compilation (types match usage in components)
- ✅ Import resolution (generated files exist)
- ✅ Type safety (no type mismatches)

The build does NOT validate:

- ❌ Whether generated types match the current API
- ❌ Whether types are stale if API changed

**Important:** Always regenerate the client after API changes and commit the updated generated files.

### Generated Files

Generated files are **checked into git** for simpler CI/CD (no FastAPI dependency during build). When regenerating:

1. Review the diff to understand API changes
2. Update components using the API if breaking changes occurred
3. Run tests: `pnpm test`
4. Run build: `pnpm build`
5. Commit the changes

## Learn More

To learn more about Next.js, take a look at the following resources:

- [Next.js Documentation](https://nextjs.org/docs) - learn about Next.js features and API.
- [Learn Next.js](https://nextjs.org/learn) - an interactive Next.js tutorial.

You can check out [the Next.js GitHub repository](https://github.com/vercel/next.js) - your feedback and contributions are welcome!

## Deploy on Vercel

The easiest way to deploy your Next.js app is to use the [Vercel Platform](https://vercel.com/new?utm_medium=default-template&filter=next.js&utm_source=create-next-app&utm_campaign=create-next-app-readme) from the creators of Next.js.

Check out our [Next.js deployment documentation](https://nextjs.org/docs/app/building-your-application/deploying) for more details.
