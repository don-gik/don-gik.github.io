/** @type {import('tailwindcss').Config} */
module.exports = {
  darkMode: 'class', // or 'media'
  content: [
    "./**/*.{html,md,markdown,liquid}",
    "!./_site/**/*",
    "!./node_modules/**/*"
  ],
  // Prevent Tailwind preflight from resetting base element styles (e.g., h1/h2 margins)
  corePlugins: { preflight: false },
  theme: { extend: {} },
  safelist: [
    // keep arbitrary OKLCH classes used in your cards
    'from-[oklch(0.55_0.17_270)]',
    'to-[oklch(0.62_0.20_275)]',
    'focus-visible:ring-[oklch(0.88_0.06_270_/_0.6)]'
  ],
  plugins: []
};
