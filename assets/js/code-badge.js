document.addEventListener('DOMContentLoaded', () => {
  const wrapWrappers = new Set();
  const hasResizeObserver = typeof ResizeObserver !== 'undefined';
  const WRAP_THRESHOLD = 4;

  // 공통 셀렉터
  const WRAP_CLASSES = ['code-wrap', 'code-wrap-word', 'code-wrap-char'];
  const WRAP_SELECTOR = WRAP_CLASSES.map((cls) => `.${cls}`).join(', ');
  const WRAPPER_SELECTOR = 'figure.highlight, div.highlighter-rouge, div.highlight, pre';

  // ---- helpers -------------------------------------------------
  const getWrapper = (el) => {
    if (!el || !el.closest) return null;
    let w = el.closest('figure.highlight, div.highlighter-rouge, div.highlight, pre');
    if (!w) return null;
    if (
      w.matches('pre') &&
      w.parentElement &&
      w.parentElement.matches('figure.highlight, div.highlighter-rouge, div.highlight, .code-file')
    ) {
      w = w.parentElement;
    }
    return w;
  };

  const uniqueWrappers = (root = document) => {
    const set = new Set();
    root.querySelectorAll(WRAPPER_SELECTOR).forEach((n) => {
      const w = getWrapper(n);
      if (w) set.add(w);
    });
    return [...set];
  };

  const getWrapContainer = (element) => {
    if (!element || typeof element.closest !== 'function') return null;
    if (WRAP_CLASSES.some((cls) => element.classList.contains(cls))) return element;
    return element.closest(WRAP_SELECTOR);
  };
  const isWrapCandidate = (element) => !!getWrapContainer(element);

  const updateRowWrapState = (element) => {
    const container = getWrapContainer(element) || element;
    if (!container) return;
    const rows = container.querySelectorAll('.code-frame__row');
    rows.forEach((row) => {
      const codeCell = row.querySelector('.code-frame__cell--code');
      if (!codeCell) return;
      const cs = getComputedStyle(codeCell);
      const lh = parseFloat(cs.lineHeight) || (parseFloat(cs.fontSize) * 1.2);
      const pt = parseFloat(cs.paddingTop) || 0;
      const pb = parseFloat(cs.paddingBottom) || 0;
      const contentHeight = codeCell.scrollHeight - pt - pb;
      const visualLines = Math.round(contentHeight / lh);
      const isWrapped = visualLines > 1;
      row.classList.toggle('is-softwrapped', isWrapped);
    });
  };

  const updateWrapState = (element) => {
    const container = getWrapContainer(element);
    if (!container) return;
    const codeAreas = container.querySelectorAll('.code-frame__cell--code, pre');
    let wrapped = false;
    codeAreas.forEach((area) => {
      if (wrapped || !area) return;
      const target = area.tagName === 'CODE' && area.parentElement ? area.parentElement : area;
      const diff = target.scrollWidth - target.clientWidth;
      if (diff > WRAP_THRESHOLD) wrapped = true;
    });
    container.classList.toggle('code-wrap-is-active', wrapped);
    // After toggling wrap mode, update per-row wrap flags in next frame
    requestAnimationFrame(() => updateRowWrapState(container));
  };

  const observeWrap = (element) => {
    const container = getWrapContainer(element);
    if (!container || wrapWrappers.has(container)) return;
    wrapWrappers.add(container);
    requestAnimationFrame(() => updateWrapState(container));
    if (hasResizeObserver) {
      const observer = new ResizeObserver(() => updateWrapState(container));
      observer.observe(container);
      container.__codeWrapObserver = observer;
    }
  };

  const nice = (raw) => {
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

  const getCode = (wrapper) =>
    wrapper.querySelector('pre code') ||
    wrapper.querySelector('code') ||
    wrapper.querySelector('.code-frame');

  const getText = (wrapper) => {
    const c = getCode(wrapper);
    if (!c) return wrapper.innerText.trimEnd();
    if (c.classList.contains('code-frame')) {
      const raw = c.dataset.raw;
      if (raw) return raw;
    }
    const clone = c.cloneNode(true);
    clone.querySelectorAll('.gutter, .code-frame__gutter, .code-frame__cell--gutter').forEach((el) => el.remove());
    const normalized = clone.querySelector('.code-frame__code, .code-frame__cell--code');
    if (normalized) return normalized.innerText.trimEnd();
    return clone.innerText.trimEnd();
  };

  const normalizeRougeTable = (wrapper) => {
    const table = wrapper.querySelector('table.rouge-table');
    if (!table || table.dataset.normalized === 'true') return;

    const gutterPre = table.querySelector('td.gutter pre');
    const codePre   = table.querySelector('td.code pre');
    if (!codePre) { table.dataset.normalized = 'true'; return; }

    const frame = document.createElement('div');
    frame.className = 'code-frame';

    const cleanSplit = (value, mapper = (x) => x) => {
      if (!value) return [];
      const arr = mapper(value).split('\n');
      if (arr.length && arr[arr.length - 1] === '') arr.pop();
      return arr;
    };

    const hasGutter  = !!gutterPre;
    const gutterLines= cleanSplit(hasGutter ? gutterPre.innerText : '');
    const codeLines  = cleanSplit(codePre.innerHTML, (v) => v);
    const codePlain  = cleanSplit(codePre.innerText).join('\n');
    const rows       = Math.max(gutterLines.length, codeLines.length);

    for (let i = 0; i < rows; i += 1) {
      const row = document.createElement('div');
      row.className = 'code-frame__row';

      const gutterCell = document.createElement('span');
      gutterCell.className = 'code-frame__cell code-frame__cell--gutter';
      gutterCell.textContent = hasGutter ? (gutterLines[i] || '') : String(i + 1);
      row.appendChild(gutterCell);

      const codeCell = document.createElement('span');
      codeCell.className = 'code-frame__cell code-frame__cell--code';
      const htmlLine = codeLines[i] || '';
      codeCell.innerHTML = htmlLine.length ? htmlLine : '&nbsp;';
      row.appendChild(codeCell);

      frame.appendChild(row);
    }

    frame.dataset.raw = codePlain;
    table.replaceWith(frame);

    if (isWrapCandidate(wrapper)) requestAnimationFrame(() => updateWrapState(wrapper));
  };

  const buildLineNumbersForPlainPre = (wrapper) => {
    if (wrapper.querySelector('.code-frame')) return;

    const pre = wrapper.querySelector('pre');
    const codeFallback = wrapper.querySelector(':scope > code') || wrapper.querySelector('code');
    const host = pre || wrapper; // frame을 붙일 대상

    const codeEl = pre ? (pre.querySelector('code') || pre) : codeFallback;
    if (!codeEl || codeEl.dataset.frameBuilt === 'true') return;

    const normalizeLines = (value) => {
      if (!value) return [];
      const parts = value.replace(/\r/g, '').split('\n');
      while (parts.length && parts[parts.length - 1] === '') parts.pop();
      return parts;
    };

    const htmlLines = normalizeLines(codeEl.innerHTML);
    const textLines = normalizeLines(codeEl.textContent);
    const rows = Math.max(htmlLines.length, textLines.length);
    if (!rows) return;

    const frame = document.createElement('div');
    frame.className = 'code-frame';
    const rawText = textLines.join('\n');

    for (let i = 0; i < rows; i += 1) {
      const row = document.createElement('div');
      row.className = 'code-frame__row';

      const gutterCell = document.createElement('span');
      gutterCell.className = 'code-frame__cell code-frame__cell--gutter';
      gutterCell.textContent = String(i + 1);
      row.appendChild(gutterCell);

      const codeCell = document.createElement('span');
      codeCell.className = 'code-frame__cell code-frame__cell--code';
      const htmlLine = htmlLines[i] || '';
      codeCell.innerHTML = htmlLine.length ? htmlLine : '&nbsp;';
      row.appendChild(codeCell);

      frame.appendChild(row);
    }

    frame.dataset.raw = rawText;

    // 기존 내용을 비우고 frame 삽입
    if (pre) {
      (pre.querySelector('code') || pre).innerHTML = '';
      (pre.querySelector('code') || pre).appendChild(frame);
    } else if (codeFallback) {
      codeFallback.replaceWith(frame);
    } else {
      host.appendChild(frame);
    }

    codeEl.dataset.frameBuilt = 'true';
    if (isWrapCandidate(wrapper)) requestAnimationFrame(() => updateWrapState(wrapper));
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
    if (!getCode(wrapper)) return;

    normalizeRougeTable(wrapper);
    buildLineNumbersForPlainPre(wrapper);

    if (getComputedStyle(wrapper).position === 'static') wrapper.style.position = 'relative';
    if (!wrapper.classList.contains('code-wrap') &&
        !wrapper.classList.contains('code-scroll') &&
        !wrapper.classList.contains('code-wrap-char')) {
      wrapper.classList.add('code-scroll');
    }

    if (!wrapper.dataset.badged) {
      const badge = document.createElement('span');
      badge.className = 'code-badge';
      badge.textContent = nice(detectLang(wrapper));
      wrapper.appendChild(badge);
      wrapper.dataset.badged = '1';
    }

    if (!wrapper.dataset.copiedBtn) {
      const copy = document.createElement('button');
      copy.type = 'button';
      copy.className = 'copy-btn';
      copy.textContent = 'Copy';
      copy.addEventListener('click', async () => {
        const text = getText(wrapper);
        try { await navigator.clipboard.writeText(text); }
        catch {
          const ta = document.createElement('textarea');
          ta.value = text; document.body.appendChild(ta);
          ta.select(); document.execCommand('copy'); ta.remove();
        }
        const prev = copy.textContent; copy.textContent = 'Copied!';
        setTimeout(()=>copy.textContent = prev, 1200);
      });
      wrapper.appendChild(copy);
      wrapper.dataset.copiedBtn = '1';
    }
    wrapper.classList.add('code-processed');
    observeWrap(wrapper);
  };

  // ---- init ----------------------------------------------------
  uniqueWrappers(document).forEach(process);

  window.addEventListener('resize', () => {
    wrapWrappers.forEach((wrapper) => updateWrapState(wrapper));
  });

  document.querySelectorAll('details').forEach(d => {
    d.addEventListener('toggle', () => {
      if (d.open) {
        uniqueWrappers(d).forEach(process);
        d.querySelectorAll(WRAP_SELECTOR).forEach(observeWrap);
      }
    });
  });

  setTimeout(() => {
    wrapWrappers.forEach((wrapper) => updateWrapState(wrapper));
  }, 100);
});
