(function () {
  const mql = window.matchMedia('(max-width: 720px)');
  const header = document.querySelector('.site-header');
  if (!header) return;

  let lastY = window.scrollY || 0;
  let ticking = false;
  let enabled = false;

  function onScroll() {
    if (!enabled) return;
    const currentY = window.scrollY || 0;
    if (!ticking) {
      window.requestAnimationFrame(() => {
        const delta = currentY - lastY;
        const pastTop = currentY > 24; // don't hide right at the very top
        if (delta > 6 && pastTop) {
          header.classList.add('site-header--hidden');
        } else if (delta < -6) {
          header.classList.remove('site-header--hidden');
        }
        lastY = currentY;
        ticking = false;
      });
      ticking = true;
    }
  }

  function enable() {
    if (enabled) return;
    enabled = true;
    header.classList.remove('site-header--hidden');
    window.addEventListener('scroll', onScroll, { passive: true });
  }

  function disable() {
    if (!enabled) return;
    enabled = false;
    window.removeEventListener('scroll', onScroll);
    header.classList.remove('site-header--hidden');
  }

  function handleChange(e) {
    if (e.matches) enable(); else disable();
  }

  // init
  handleChange(mql);
  mql.addEventListener ? mql.addEventListener('change', handleChange) : mql.addListener(handleChange);
})();

