---
title: React + Three Demo
layout: default
tailwind: true
react: true
permalink: /react-three/
seo:
  title: "React + Three.js Demo | Don-gik Blog"
  description: "See a live example of a React Three Fiber scene running on the blog, complete with bundle setup notes."
description: "Interactive React Three Fiber demo that renders a spinning cube and shows how to enable the React bundle on any page."
---

<h1 class="text-2xl font-semibold mb-4">React + Three.js (R3F) Demo</h1>

<p class="mb-4">A spinning cube rendered with <code>@react-three/fiber</code>. This page loads a bundled React script and mounts into the element below.</p>

<div data-r3f-canvas class="w-full h-96 rounded-md border border-slate-700"></div>

<p class="text-sm text-slate-400 mt-4">To use on any page, set <code>react: true</code> in front matter and add an element with <code>data-r3f-canvas</code>.</p>
