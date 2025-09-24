require 'nokogiri'

# Server-side transform for code blocks to ensure consistent line numbers and wrapping
# - Converts Rouge's table output into a .code-frame with gutter and code cells
# - Adds line numbers for plain <pre><code> blocks when present

module DonGik
  class CodeFrameTransformer
    SELECTORS = [
      'figure.highlight table.rouge-table',
      'div.highlighter-rouge table.rouge-table',
      'div.highlight table.rouge-table'
    ].freeze

    def self.process_html(html)
      return html unless html && html.include?('rouge-table') || html.include?('<pre')

      doc = Nokogiri::HTML::Document.parse(html)

      # Transform Rouge tables to .code-frame
      doc.css(SELECTORS.join(',')).each do |table|
        gutter_pre = table.at_css('td.gutter pre')
        code_pre   = table.at_css('td.code pre')
        next unless code_pre

        has_gutter = !gutter_pre.nil?
        gutter_lines = split_lines(gutter_pre&.text)
        code_lines_html = split_lines(code_pre.inner_html)
        code_plain = split_lines(code_pre.text).join("\n")

        frame = Nokogiri::XML::Node.new('div', doc)
        frame['class'] = 'code-frame'
        frame['data-raw'] = code_plain

        rows = [gutter_lines.length, code_lines_html.length].max
        (0...rows).each do |i|
          row = Nokogiri::XML::Node.new('div', doc)
          row['class'] = 'code-frame__row'

          gut = Nokogiri::XML::Node.new('span', doc)
          gut['class'] = 'code-frame__cell code-frame__cell--gutter'
          gut.content = has_gutter ? (gutter_lines[i] || '') : (i + 1).to_s
          row.add_child(gut)

          code_cell = Nokogiri::XML::Node.new('span', doc)
          code_cell['class'] = 'code-frame__cell code-frame__cell--code'
          html_line = code_lines_html[i] || ''
          code_cell.inner_html = html_line.empty? ? '&nbsp;' : html_line
          row.add_child(code_cell)

          frame.add_child(row)
        end

        table.replace(frame)
      end

      # Add numbers for plain <pre><code> blocks not handled by Rouge table
      doc.css('figure.highlight pre code, div.highlighter-rouge pre code, div.highlight pre code').each do |code|
        # Skip if already wrapped
        next if code.at_css('.code-frame')

        html_lines = split_lines(code.inner_html)
        text_lines = split_lines(code.text)
        rows = [html_lines.length, text_lines.length].max
        next if rows.zero?

        frame = Nokogiri::XML::Node.new('div', doc)
        frame['class'] = 'code-frame'
        frame['data-raw'] = text_lines.join("\n")

        (0...rows).each do |i|
          row = Nokogiri::XML::Node.new('div', doc)
          row['class'] = 'code-frame__row'

          gut = Nokogiri::XML::Node.new('span', doc)
          gut['class'] = 'code-frame__cell code-frame__cell--gutter'
          gut.content = (i + 1).to_s
          row.add_child(gut)

          code_cell = Nokogiri::XML::Node.new('span', doc)
          code_cell['class'] = 'code-frame__cell code-frame__cell--code'
          html_line = html_lines[i] || ''
          code_cell.inner_html = html_line.empty? ? '&nbsp;' : html_line
          row.add_child(code_cell)

          frame.add_child(row)
        end

        # Clear and insert frame
        code.children.remove
        code.add_child(frame)
      end

      doc.to_html
    rescue => e
      warn "[code_frame] Error: #{e.class}: #{e.message}"
      html
    end

    def self.split_lines(value)
      return [] unless value
      parts = value.gsub("\r", '').split("\n")
      parts.pop while parts.any? && parts.last == ''
      parts
    end
  end
end

Jekyll::Hooks.register :pages, :post_render do |page|
  page.output = DonGik::CodeFrameTransformer.process_html(page.output)
end

Jekyll::Hooks.register :posts, :post_render do |post|
  post.output = DonGik::CodeFrameTransformer.process_html(post.output)
end

