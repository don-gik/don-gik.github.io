(function () {
  const input = document.querySelector('[data-search-input]');
  const resultsList = document.querySelector('[data-search-results]');
  const status = document.querySelector('[data-search-status]');

  if (!input || !resultsList) return;

  input.disabled = true;

  const SEARCH_DATA_URL = document.body.getAttribute('data-search-json') || '/search.json';
  const MIN_QUERY_LENGTH = 2;
  const locale = document.documentElement.getAttribute('lang') || 'en';

  let documents = [];
  let documentsById = new Map();
  let index = null;
  let isReady = false;
  let debounceTimer = null;

  function setStatus(message, isError) {
    if (!status) return;
    status.textContent = message || '';
    status.classList.toggle('is-error', !!isError);
    status.hidden = !message;
  }

  function truncate(text, maxLength) {
    if (!text) return '';
    if (text.length <= maxLength) return text;
    const truncated = text.slice(0, maxLength);
    const lastSpace = truncated.lastIndexOf(' ');
    return `${truncated.slice(0, lastSpace > 40 ? lastSpace : maxLength)}…`;
  }

  function normalizeList(value) {
    if (!value) return [];
    return Array.isArray(value) ? value : [value];
  }

  function formatMeta(doc) {
    const metaParts = [];

    if (doc.date) {
      const dateObj = new Date(doc.date);
      if (!Number.isNaN(dateObj.getTime())) {
        metaParts.push(new Intl.DateTimeFormat(locale, { year: 'numeric', month: 'short', day: 'numeric' }).format(dateObj));
      }
    }

    if (doc.collection) {
      const label = doc.collection === 'posts' ? 'Post' : doc.collection === 'pages' ? 'Page' : doc.collection.replace(/[-_]/g, ' ');
      metaParts.push(label.replace(/\b\w/g, (char) => char.toUpperCase()));
    }

    return metaParts.join(' · ');
  }

  function renderResults(results) {
    resultsList.innerHTML = '';

    if (!results || results.length === 0) {
      const empty = document.createElement('li');
      empty.className = 'search-result search-result--empty';
      const trimmed = input.value.trim();
      empty.textContent = trimmed.length < MIN_QUERY_LENGTH && trimmed.length > 0
        ? `Type at least ${MIN_QUERY_LENGTH} characters to search.`
        : trimmed
          ? 'No matching results found.'
          : 'Start typing to search posts and pages.';
      resultsList.appendChild(empty);
      return;
    }

    results.slice(0, 25).forEach(({ ref, score }) => {
      const doc = documentsById.get(ref);
      if (!doc) return;

      const item = document.createElement('li');
      item.className = 'search-result';

      const anchor = document.createElement('a');
      anchor.className = 'search-result__link';
      anchor.href = doc.url;

      const title = document.createElement('span');
      title.className = 'search-result__title';
      title.textContent = doc.title || doc.url;
      anchor.appendChild(title);

      const metaLabel = formatMeta(doc);
      if (metaLabel) {
        const meta = document.createElement('span');
        meta.className = 'search-result__meta';
        meta.textContent = metaLabel;
        anchor.appendChild(meta);
      }

      if (doc.excerpt) {
        const excerpt = document.createElement('span');
        excerpt.className = 'search-result__excerpt';
        excerpt.textContent = truncate(doc.excerpt, 200);
        anchor.appendChild(excerpt);
      }

      const tags = normalizeList(doc.tags);
      if (tags.length > 0) {
        const tagEl = document.createElement('span');
        tagEl.className = 'search-result__tags';
        tagEl.textContent = tags.map((tag) => `#${tag}`).join('  ');
        anchor.appendChild(tagEl);
      }

      item.appendChild(anchor);
      resultsList.appendChild(item);
    });
  }

  function buildQueryTokens(query) {
    const trimmed = query.trim();
    if (trimmed.length < MIN_QUERY_LENGTH) return null;

    const tokens = lunr.tokenizer(trimmed.toLowerCase());
    if (!tokens || tokens.length === 0) return null;
    return tokens.map((token) => token.toString());
  }

  function performSearch(query) {
    if (!isReady || !index) return;

    const tokens = buildQueryTokens(query);
    if (!tokens) {
      renderResults([]);
      return;
    }

    try {
      const results = index.query((q) => {
        tokens.forEach((token) => {
          q.term(token, { boost: 12 });
          q.term(token, { boost: 8, wildcard: lunr.Query.wildcard.TRAILING });

          if (token.length > 4) {
            q.term(token, { editDistance: 1, boost: 6 });
          }
        });
      });

      setStatus(results.length ? '' : '');
      renderResults(results);
    } catch (error) {
      console.error('Lunr search failed', error);
      setStatus('Something went wrong while searching.', true);
    }
  }

  function hydrateIndex(data) {
    documents = data.map((doc, index) => ({
      ...doc,
      id: doc.id || String(index),
      tags: normalizeList(doc.tags),
    }));

    documentsById = new Map(documents.map((doc) => [doc.id, doc]));

    index = lunr(function () {
      this.use(lunr.ko);
      this.ref('id');
      this.field('title', { boost: 10 });
      this.field('excerpt', { boost: 6 });
      this.field('content');
      this.field('categories');
      this.field('tags');

      documents.forEach((doc) => {
        this.add({
          ...doc,
          categories: normalizeList(doc.categories).join(' '),
          tags: doc.tags.join(' '),
        });
      });
    });

    isReady = true;
    setStatus('');
    input.disabled = false;
    renderResults([]);
  }

  function loadSearchIndex() {
    if (typeof lunr === 'undefined') {
      setStatus('Search failed to load. Please refresh the page.', true);
      return;
    }

    setStatus('Loading index…');

    fetch(SEARCH_DATA_URL, { credentials: 'same-origin' })
      .then((response) => {
        if (!response.ok) throw new Error(`HTTP ${response.status}`);
        return response.json();
      })
      .then((data) => {
        hydrateIndex(Array.isArray(data) ? data : []);
        if (input.value) {
          performSearch(input.value);
        }
      })
      .catch((error) => {
        console.error('Failed to load search index', error);
        setStatus('Unable to load search index. Please try again later.', true);
        input.disabled = false;
      });
  }

  input.addEventListener('input', (event) => {
    const value = event.target.value;
    window.clearTimeout(debounceTimer);
    debounceTimer = window.setTimeout(() => {
      performSearch(value);
    }, 170);
  });

  if (document.readyState === 'complete') {
    loadSearchIndex();
  } else {
    window.addEventListener('load', loadSearchIndex, { once: true });
  }
})();
