# don-gik.github.io
My static website

## Local Development
- Install deps: `bundle install`
- Install Node deps (for Tailwind): `npm ci`
- Serve with future posts visible (recommended):
  `bundle exec jekyll serve --config _config.yml,_config.local.yml`
  - This shows future-dated posts so Categories/Tags pages have content.
  - Alternatively, use `bundle exec jekyll serve --future`.
  - Do not use `--safe` (it disables custom plugins like taxonomy/code-frame).

- Tailwind workflow:
  - Watch CSS during dev: `npm run dev` (runs Jekyll + Tailwind watcher)
  - One-off CSS build: `npm run build:css`

## Deployment (GitHub Pages via Actions)
- This repo deploys with GitHub Actions using `.github/workflows/pages.yml`.
- Requirements (one-time):
  - In GitHub: Settings → Pages → Build and deployment → Source: `GitHub Actions`.
- On push to `main`, the workflow:
  - Checks out code, sets up Node 20 + Ruby 3.2.2.
  - Installs npm dev deps (`npm ci`) and builds Tailwind CSS to `assets/css/main.css`.
  - Installs gems (bundler cache) and builds Jekyll into `_site` with `JEKYLL_ENV=production`.
  - Uploads the artifact and deploys to the `github-pages` environment.
- Manual deploy: Actions → "Build & Deploy Jekyll" → Run workflow.
