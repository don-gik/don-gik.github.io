# don-gik.github.io
My static website

Local development
- Install deps: `bundle install`
- Serve with future posts visible (recommended):
  `bundle exec jekyll serve --config _config.yml,_config.local.yml`
  - This shows future-dated posts so Categories/Tags pages have content.
  - Alternatively, use `bundle exec jekyll serve --future`.
  - Do not use `--safe` (it disables custom plugins like taxonomy/code-frame).
