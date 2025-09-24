require 'jekyll'

module DonGik
  # Generates static pages for each category and tag at build time.
  # - Output paths:
  #   /categories/<slug>/index.html
  #   /tags/<slug>/index.html
  # - Uses layout: 'taxon' (see _layouts/taxon.html)
  class TaxonomyGenerator < Jekyll::Generator
    safe true
    priority :low

    def generate(site)
      cat_count = gen_for(site, :category, site.categories)
      tag_count = gen_for(site, :tag, site.tags)
      Jekyll.logger.info("taxonomy", "generated #{cat_count} categories, #{tag_count} tags")
    end

    private

    def gen_for(site, taxon, map)
      created = 0
      map.each_key do |name|
        next if name.to_s.strip.empty?
        slug = Jekyll::Utils.slugify(name)
        dir  = File.join(taxon == :category ? 'categories' : 'tags', slug)
        page = Jekyll::PageWithoutAFile.new(site, site.source, dir, 'index.html')
        page.data['layout'] = 'taxon'
        page.data['taxon']  = (taxon == :category ? 'category' : 'tag')
        page.data['term']   = name
        page.data['name']   = name
        page.data['title']  = (taxon == :category ? "Category: #{name}" : "Tag: #{name}")
        page.data['permalink'] = "/#{taxon == :category ? 'categories' : 'tags'}/#{slug}/"
        site.pages << page
        created += 1
      end
      created
    end
  end
end
