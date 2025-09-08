(function () {
  function codeText(block) {
    const el = block.querySelector('td.code pre, pre.highlight, pre > code, pre');
    return el ? el.innerText.trimEnd() : '';
  }
  async function addCopy(block) {
    if (block.classList.contains('has-copy')) return;
    const btn = document.createElement('button');
    btn.className = 'copy-btn';
    btn.type = 'button';
    btn.textContent = 'Copy';
    btn.addEventListener('click', async () => {
      const text = codeText(block);
      try {
        await navigator.clipboard.writeText(text);
        btn.textContent = 'Copied!';
      } catch {
        const ta = document.createElement('textarea');
        ta.value = text; document.body.appendChild(ta);
        ta.select(); document.execCommand('copy');
        document.body.removeChild(ta);
        btn.textContent = 'Copied!';
      }
      setTimeout(() => (btn.textContent = 'Copy'), 1200);
    });
    block.appendChild(btn);
    block.classList.add('has-copy');
  }

  document.addEventListener('DOMContentLoaded', () => {
    document.querySelectorAll('figure.highlight, div.highlighter-rouge')
      .forEach(addCopy);

    // 접기/펼치기 안의 코드도 열릴 때 버튼 부착
    document.querySelectorAll('details.code-file').forEach(d => {
      d.addEventListener('toggle', () => {
        if (d.open) d.querySelectorAll('figure.highlight, div.highlighter-rouge')
          .forEach(addCopy);
      });
    });
  });
})();
