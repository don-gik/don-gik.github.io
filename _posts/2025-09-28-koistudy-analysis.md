---
layout: single
title: "Koistudy 취약점 분석"
excerpt: "혼자 알아낸거밖에 없어요"
classes: wide
categories: [web hacking]
tags: [coding, web hacking]
math: true
toc: false
tailwind: true
---

<style>
    .page__content figure > figcaption {
        text-align: center !important;
        margin: -0.4rem 0 0 !important;
        padding: 0 !important;
        font-size: .95em;
        line-height: 1.35;
        background: transparent;
        border: 0;
    }
    img.center {
        display: block;
        margin-left: auto;
        margin-right: auto;
    }
    .lh-boost { line-height: 2.7; }

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
    width: min(100%);
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


<p1>조금씩 더 추가할 예정입니다.</p1>

<p1>각 취약점은 h3태그로 제목이 구성되어있습니다.</p1>


<div class="w-full max-w-none mx-0 rounded-lg group transition-transform duration-300 ease-in-out transform hover:-translate-y-1 bg-gray-900">


    <div class="overlay"></div>

    <div class="relative z-10 p-6 flex flex-col justify-start items-start">

        <h3 class="text-xl font-semibold text-white">1. 비밀번호 평문 전송</h3>


        <p class="mt-2 text-sm text-white/90">
            로그인은 php로 구현되어있으며,

            <a href="https://koistudy.net/index.php?act=procMemberLogin"
                class="underline decoration-2 decoration-white/40 text-white/90 transition-colors duration-200 group-hover:text-white">
                여기</a>를 통해 POST요청으로 로그인이 되어있다. 이때 비밀번호가 평문으로 전송된다.
        </p>
        <p class="mt-2 text-sm text-white/90">
            이는 Packet Sniffing으로 쉽게 비밀번호가 획득될 수 있다는 것이다.
        </p>
    </div>
</div>

<div class="w-full max-w-none mx-0 rounded-lg group transition-transform duration-300 ease-in-out transform hover:-translate-y-1 bg-gray-900">


    <div class="overlay"></div>

    <div class="relative z-10 p-6 flex flex-col justify-start items-start">

        <h3 class="text-xl font-semibold text-white">2. Runtime Error 메시지 제공</h3>


        <p class="mt-2 text-sm text-white/90">
            Runtime 에러를 볼 수 있다는 것은 테스트 케이스 누수와 파일 디렉토리 구성에 접근이 가능하다는 것이다.
            이는 치명적인 공격에 사용될 수도 있다.<br>
        </p>
        <p class="mt-2 text-sm text-white/90">
            확인 결과 이전의 Koistudy보다 개선된 점은 이제 코드를 VM에서 실행한다는 것이다.
            그러나 사실상 PS와 관련이 없는 dirent.h 등의 header를 지원한다는 점은 취약점이 될 수 있다.
        </p>

        <p class="mt-2 text-sm text-white/90">
            <br>
            <br>
            VM에서 Linux 명령어를 실행할 수 있다는 취약점이 확인되었다.
            또한 VM에 파일을 생성하는 것이 가능하다는 취약점도 발견되었다.
        </p>
    </div>
</div>