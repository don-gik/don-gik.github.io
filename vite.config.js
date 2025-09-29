import { defineConfig } from 'vite';
import react from '@vitejs/plugin-react';

// Build a single self-executing bundle we can include in Jekyll
export default defineConfig({
  plugins: [react()],
  define: {
    'process.env.NODE_ENV': JSON.stringify('production'),
    'global': 'window',
  },
  build: {
    lib: {
      entry: 'assets/react/main.jsx',
      name: 'SiteReactApp',
      formats: ['iife'],
      fileName: () => 'site-react-app.js',
    },
    outDir: 'assets/react-dist',
    emptyOutDir: true,
  },
});
