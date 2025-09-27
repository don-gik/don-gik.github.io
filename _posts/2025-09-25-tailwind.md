---
layout: single
title: "TailWind 공부 1일차"
excerpt: "TailWind 어려워요"
classes: wide
categories: [web dev]
tags: [web dev, my life]
math: true
toc: false
tailwind: true
---

<style>
  .glass-card {   
    background: rgba(255, 255, 255, 0.18);
    border-radius: 20px;
    border: 1px solid rgba(255, 255, 255, 0.3);
    box-shadow:
      0 8px 32px rgba(0, 0, 0, 0.1),
      inset 0 1px 0 rgba(255, 255, 255, 0.5),
      inset 0 -1px 0 rgba(255, 255, 255, 0.1),
      inset 0 0 0px 0px rgba(255, 255, 255, 0);
    position: relative;
    overflow: hidden;

    margin-inline: auto;
    width: min(100%, 28rem);
  }

  .glass-card::before {
    content: '';
    position: absolute; top: 0; left: 0; right: 0; height: 1px;
    background: linear-gradient(90deg, transparent, rgba(255,255,255,0.8), transparent);
    pointer-events: none;
  }

  .glass-card::after {
    content: '';
    position: absolute; top: 0; left: 0; width: 1px; height: 100%;
    background: linear-gradient(180deg, rgba(255,255,255,0.8), transparent, rgba(255,255,255,0.3));
    pointer-events: none;
  }

  /* blur here... */
  .glass-card .overlay {
    position: absolute; inset: 0;
    background: rgba(0, 0, 0, 0.4);
    backdrop-filter: blur(8px) saturate(1.1);
    -webkit-backdrop-filter: blur(8px) saturate(1.1);
  }
</style>

<div class="glass-card group
            transition-transform duration-300 ease-in-out transform  hover:-translate-y-0.5">
  <a href="https://arxiv.org/abs/1706.03762"
     class="inline-block underline decoration-2 decoration-white/40 text-white/90 transition-colors duration-200 group-hover:text-white">
    <!-- bg image -->
    <img src="/assets/images/base/1.png" alt=""
        class="absolute inset-0 h-full w-full object-cover" />
    <!-- blur overlay -->
    <div class="overlay"></div>
    <!-- content -->
    <div class="relative grid min-h-[220px] grid-rows-[1fr_auto] gap-3 p-4">
      <div class="space-y-1">
        <div class="text-xs uppercase tracking-wide text-white/80">Paper</div>
        <h3 class="text-base font-extrabold leading-tight text-white">
          Attention Is All You Need
        </h3>
        <p class="text-sm leading-snug text-white/90">
          Original Transformer paper. Abstract, model, results, and the reason half the internet now says “just use attention.”
        </p>
      </div>
      <div class="flex items-center justify-between text-sm text-white/90">
        <span>arXiv: 1706.03762</span>
        <span class="transition-transform group-hover:translate-x-0.5">↗</span>
      </div>
    </div>
  </a>
</div>

와 너무 어려운데

Glass Morphism 만들고 싶었어서 만들어봤어요 react랑 three.js 쓰면 더 예뻐진다네요 그건 너무 어려움...

일단 TailWind CSS의 기본적인 이해는 된것같은데 CSS랑 같이 쓰면서부터 이해가 안되네요 도와줘요

<div class="code-wrap-char">
{% highlight html linenos %}
<style>
  .glass-card {   
    background: rgba(255, 255, 255, 0.18);
    border-radius: 20px;
    border: 1px solid rgba(255, 255, 255, 0.3);
    box-shadow:
      0 8px 32px rgba(0, 0, 0, 0.1),
      inset 0 1px 0 rgba(255, 255, 255, 0.5),
      inset 0 -1px 0 rgba(255, 255, 255, 0.1),
      inset 0 0 0px 0px rgba(255, 255, 255, 0);
    position: relative;
    overflow: hidden;

    margin-inline: auto;
    width: min(100%, 28rem);
  }

  .glass-card::before {
    content: '';
    position: absolute; top: 0; left: 0; right: 0; height: 1px;
    background: linear-gradient(90deg, transparent, rgba(255,255,255,0.8), transparent);
    pointer-events: none;
  }

  .glass-card::after {
    content: '';
    position: absolute; top: 0; left: 0; width: 1px; height: 100%;
    background: linear-gradient(180deg, rgba(255,255,255,0.8), transparent, rgba(255,255,255,0.3));
    pointer-events: none;
  }

  /* blur here... */
  .glass-card .overlay {
    position: absolute; inset: 0;
    background: rgba(0, 0, 0, 0.4);
    backdrop-filter: blur(8px) saturate(1.1);
    -webkit-backdrop-filter: blur(8px) saturate(1.1);
  }
</style>

<div class="glass-card group
            transition-transform duration-300 ease-in-out transform  hover:-translate-y-0.5">
  <a href="https://arxiv.org/abs/1706.03762"
     class="inline-block underline decoration-2 decoration-white/40 text-white/90 transition-colors duration-200 group-hover:text-white">
    <!-- bg image -->
    <img src="/assets/images/base/1.png" alt=""
        class="absolute inset-0 h-full w-full object-cover" />
    <!-- blur overlay -->
    <div class="overlay"></div>
    <!-- content -->
    <div class="relative grid min-h-[220px] grid-rows-[1fr_auto] gap-3 p-4">
      <div class="space-y-1">
        <div class="text-xs uppercase tracking-wide text-white/80">Paper</div>
        <h3 class="text-base font-extrabold leading-tight text-white">
          Attention Is All You Need
        </h3>
        <p class="text-sm leading-snug text-white/90">
          Original Transformer paper. Abstract, model, results, and the reason half the internet now says “just use attention.”
        </p>
      </div>
      <div class="flex items-center justify-between text-sm text-white/90">
        <span>arXiv: 1706.03762</span>
        <span class="transition-transform group-hover:translate-x-0.5">↗</span>
      </div>
    </div>
  </a>
</div>
{% endhighlight %}
</div>