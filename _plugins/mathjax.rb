module DonGik
  # Inject MathJax (v3) into pages that need LaTeX math.
  # Usage per page: set `math: true` in front matter, or rely on
  # auto-detection of common TeX delimiters ($$..$$, \( .. \), \[ .. \]).
  class MathJaxInjector
    CONFIG_SNIPPET = <<~HTML.freeze
      <script>
        window.MathJax = {
          tex: {
            inlineMath: [['$', '$'], ['\\(', '\\)']],
            displayMath: [['$$','$$'], ['\\[','\\]']],
            processEscapes: true,
            tags: 'ams'
          },
          options: {
            skipHtmlTags: ['script','noscript','style','textarea','pre','code']
          }
        };
      </script>
      <script id="mathjax-script" async src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-chtml.js"></script>
    HTML

    def self.needs_math?(doc)
      return true if doc.data && doc.data['math']
      html = doc.output.to_s
      return false if html.nil? || html.empty?
      return true if html.include?('$$')
      return true if html.include?('\\(') || html.include?('\\[')
      false
    end

    def self.inject!(doc)
      html = doc.output.to_s
      return if html.include?('id="mathjax-script"')
      if html =~ /<\/head>/i
        doc.output = html.sub(/<\/head>/i, CONFIG_SNIPPET + "\n</head>")
      elsif html =~ /<\/body>/i
        doc.output = html.sub(/<\/body>/i, CONFIG_SNIPPET + "\n</body>")
      else
        doc.output = CONFIG_SNIPPET + html
      end
    end
  end
end

Jekyll::Hooks.register [:pages, :posts, :documents], :post_render do |doc|
  begin
    if DonGik::MathJaxInjector.needs_math?(doc)
      DonGik::MathJaxInjector.inject!(doc)
    end
  rescue => e
    warn "[mathjax] #{e.class}: #{e.message}"
  end
end

