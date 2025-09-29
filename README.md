# don-gik.github.io
My static website

## Local Development
- Install Ruby deps: `bundle install`
- Install Node deps: `npm install`
- Serve with future posts visible (recommended):
  `bundle exec jekyll serve --config _config.yml,_config.local.yml`
  - This shows future-dated posts so Categories/Tags pages have content.
  - Alternatively, use `bundle exec jekyll serve --future`.
  - Do not use `--safe` (it disables custom plugins like taxonomy/code-frame).

- Dev workflow:
  - Watch and serve everything (Jekyll + Tailwind + React build): `npm run dev`
  - One-off CSS build: `npm run build:css`
  - One-off React bundle build: `npm run build:react`

## Deployment (GitHub Pages via Actions)
- This repo deploys with GitHub Actions using `.github/workflows/pages.yml`.
- Requirements (one-time):
  - In GitHub: Settings → Pages → Build and deployment → Source: `GitHub Actions`.
- On push to `main`, the workflow:
  - Checks out code, sets up Node 20 + Ruby 3.2.2.
  - Installs npm deps (`npm ci`).
  - Runs `npm run build` which builds Tailwind CSS, builds the React bundle to `assets/react-dist/`, and runs the Jekyll build into `_site`.
  - Uploads the artifact and deploys to the `github-pages` environment.

## React + react-three-fiber
- Add `react: true` to any page's front matter to load the React bundle.
- Include an element with `data-r3f-canvas` where you want the 3D canvas mounted.

Example page: `react-three.md` → `/react-three/`.

Bundle details:
- Built via Vite to `assets/react-dist/site-react-app.js` (IIFE, self-executing, no module imports needed).
- Auto-mounts into all `[data-r3f-canvas]` nodes on DOM ready.
- Also exposes `window.SiteReactApp.mountAll()` for manual mounting if needed.
- Manual deploy: Actions → "Build & Deploy Jekyll" → Run workflow.
