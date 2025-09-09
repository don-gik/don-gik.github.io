document.addEventListener('DOMContentLoaded', () => {
  const nice = raw => {
    if (!raw) return 'text';
    const m = { ps1:'PowerShell', powershell:'PowerShell',
      sh:'Shell', bash:'Bash', zsh:'Zsh',
      js:'JavaScript', ts:'TypeScript',
      py:'Python', python:'Python',
      cs:'C#', csharp:'C#', cpp:'C++', c:'C',
      html:'HTML', css:'CSS', yaml:'YAML', yml:'YAML',
      json:'JSON', md:'Markdown' };
    const k = String(raw).toLowerCase();
    return m[k] || raw;
  };

  const getWrapper = (el) =>
    el.closest('figure.highlight, div.highlighter-rouge, div.highlight') || el;

  const getCode = (wrapper) =>
    wrapper.querySelector('pre code') || wrapper.querySelector('code');

  const getText = (wrapper) => {
    const c = getCode(wrapper);
    if (!c) return wrapper.innerText.trimEnd();

    // Rouge 줄번호(gutter) 제거
    const clone = c.cloneNode(true);
    clone.querySelectorAll('.gutter').forEach(el => el.remove());

    return clone.innerText.trimEnd();
  };

  const detectLang = (wrapper) => {
    const c = getCode(wrapper);
    const byClass = c && [...c.classList].find(x => x.startsWith('language-'));
    const lang = (c && (c.getAttribute('data-lang') || (byClass && byClass.replace('language-',''))))
              || wrapper.getAttribute('data-lang')
              || 'text';
    return lang;
  };

  const process = (rawWrapper) => {
    const wrapper = getWrapper(rawWrapper);
    if (!wrapper || wrapper.classList.contains('code-processed')) return;

    // 코드 없으면 스킵
    if (!getCode(wrapper)) return;

    // 위치 기준 고정
    const pos = getComputedStyle(wrapper).position;
    if (pos === 'static') wrapper.style.position = 'relative';

    // 기본 모드 세팅 (명시 없으면 스크롤)
    if (!wrapper.classList.contains('code-wrap') &&
        !wrapper.classList.contains('code-scroll') &&
        !wrapper.classList.contains('code-wrap-char')) {
      wrapper.classList.add('code-scroll');
    }

    // 언어 배지
    if (!wrapper.querySelector('.code-badge')) {
      const badge = document.createElement('span');
      badge.className = 'code-badge';
      badge.textContent = nice(detectLang(wrapper));
      wrapper.appendChild(badge);
    }

    // 복사 버튼
    if (!wrapper.querySelector('.copy-btn')) {
      const copy = document.createElement('button');
      copy.type = 'button';
      copy.className = 'copy-btn';
      copy.textContent = 'Copy';
      copy.addEventListener('click', async () => {
        const text = getText(wrapper);
        try {
          await navigator.clipboard.writeText(text);
        } catch {
          const ta = document.createElement('textarea');
          ta.value = text; document.body.appendChild(ta);
          ta.select(); document.execCommand('copy'); ta.remove();
        }
        const prev = copy.textContent; copy.textContent = 'Copied!';
        setTimeout(()=>copy.textContent = prev, 1200);
      });
      wrapper.appendChild(copy);
    }
    wrapper.classList.add('code-processed');
  };

  // 초기 처리
  document.querySelectorAll('figure.highlight, div.highlighter-rouge, div.highlight, pre').forEach(process);

  // details 열릴 때 처리
  document.querySelectorAll('details').forEach(d => {
    d.addEventListener('toggle', () => {
      if (d.open) d.querySelectorAll('figure.highlight, div.highlighter-rouge, div.highlight, pre').forEach(process);
    });
  });
});
