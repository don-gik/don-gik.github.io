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

    const clone = c.cloneNode(true);
    clone.querySelectorAll('.gutter, .code-frame__gutter').forEach((el) => el.remove());
    const normalized = clone.querySelector('.code-frame__code');
    if (normalized) {
      return normalized.innerText.trimEnd();
    }

    return clone.innerText.trimEnd();
  };

  const normalizeRougeTable = (wrapper) => {
    const table = wrapper.querySelector('table.rouge-table');
    if (!table || table.dataset.normalized === 'true') return;

    const gutterPre = table.querySelector('td.gutter pre');
    const codePre = table.querySelector('td.code pre');

    if (!codePre) {
      table.dataset.normalized = 'true';
      return;
    }

    const frame = document.createElement('div');
    frame.className = 'code-frame';

    if (gutterPre) {
      const gutterClone = gutterPre.cloneNode(true);
      gutterClone.classList.add('code-frame__gutter');
      frame.appendChild(gutterClone);
    }

    const codeClone = codePre.cloneNode(true);
    codeClone.classList.add('code-frame__code');
    frame.appendChild(codeClone);

    table.replaceWith(frame);
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

    normalizeRougeTable(wrapper);

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
