(function () {
  const resultsList = document.querySelector('.taxonomy-posts');
  if (!resultsList) return;

  const SEARCH_DATA_URL = document.body.getAttribute('data-search-json') || '/search.json';
  const locale = document.documentElement.getAttribute('lang') || 'en';

  let documents = [];

  function truncate(text, maxLength) {
    if (!text) return '';
    if (text.length <= maxLength) return text;
    const truncated = text.slice(0, maxLength);
    const lastSpace = truncated.lastIndexOf(' ');
    return `${truncated.slice(0, lastSpace > 40 ? lastSpace : maxLength)}…`;
  }

  function renderResults(results) {
    resultsList.innerHTML = '';

    if (!results || results.length === 0) {
      const empty = document.createElement('div');
      empty.className = 'taxonomy-empty';
      empty.textContent = 'No matching posts found.';
      resultsList.appendChild(empty);
      return;
    }

    results.forEach(doc => {
      const item = document.createElement('article');
      item.className = 'post-card';

      const anchor = document.createElement('a');
      anchor.href = doc.url;

      const title = document.createElement('h2');
      title.className = 'post-card__title';
      title.textContent = doc.title || doc.url;
      anchor.appendChild(title);

      if (doc.excerpt) {
        const excerpt = document.createElement('p');
        excerpt.className = 'post-card__excerpt';
        excerpt.textContent = truncate(doc.excerpt, 200);
        anchor.appendChild(excerpt);
      }

      const date = document.createElement('time');
      date.className = 'post-card__date';
      date.textContent = new Intl.DateTimeFormat(locale, { year: 'numeric', month: 'short', day: 'numeric' }).format(new Date(doc.date));
      anchor.appendChild(date);

      item.appendChild(anchor);
      resultsList.appendChild(item);
    });
  }

  function filterByTaxonomy(data) {
    const url = new URL(window.location.href);
    const query = url.searchParams.get('q');
    if (!query) {
      renderResults([]);
      return;
    }

    const path = url.pathname;
    const taxonomyType = path.includes('/tags/') ? 'tags' : 'categories';

    const results = data.filter(doc => {
      if (!doc[taxonomyType]) return false;
      return doc[taxonomyType].includes(query);
    });

    renderResults(results);
  }

  function loadData() {
    fetch(SEARCH_DATA_URL, { credentials: 'same-origin' })
      .then(response => response.json())
      .then(data => {
        documents = data;
        filterByTaxonomy(documents);
      })
      .catch(error => {
        console.error('Failed to load search data', error);
        resultsList.innerHTML = '<p class="is-error">Failed to load posts.</p>';
      });
  }

  loadData();
})();
