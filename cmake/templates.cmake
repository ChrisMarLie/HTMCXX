#-------------------- elements --------------------

set(tags_template 
"    
    class {template} final : public html_tag<{template}>
    {
    public:
        using html_tag<{template}>::html_tag;
    };
    
    //----------------------------------------------------------------------------------
")

set(header_tags_template 
"export module htmcxx:tags.generated;
export import :tags.core;

export namespace htmcxx::tags
{\n")

set(footer_tags_template 
"
} //namespace htmcxx::tags
")

set(tags_list a abbr acronym address applet area article aside audio 
                  b base basefont bdi bdo big blockquote body br button 
                  canvas caption center cite code col colgroup 
                  data datalist dd del details dfn div dl dt 
                  em embed 
                  fieldset figcaption figure font footer form frame frameset 
                  h1 h2 h3 h4 h5 h6 head header hr html 
                  i iframe img input ins 
                  kbd 
                  label legend li link 
                  main map mark menu menuitem meter 
                  nav noframes noscript 
                  object ol optgroup option output 
                  p param picture pre progress 
                  q 
                  rp rt rtc ruby rb 
                  s samp script section select small source span strike strong style sub summary sup 
                  table tbody td textarea tfoot th thead time title tr track tt 
                  u ul 
                  var video
                  wbr)

#-------------------- attributes --------------------

set(attributes_template 
"
    class {template} : public html_attribute<{template}>
    {
    public:
        {template}(const std::string &value) : html_attribute{value} {}
    };

    //----------------------------------------------------------------------------------
")

set(header_attributes_template 
"module;

#include <string>

export module htmcxx:attributes.generated;
export import :attributes.core;

export namespace htmcxx::attributes
{\n")

set(footer_attributes_template 
"
} //namespace htmcxx::attributes
")

set(attributes_list accept  accesskey action align allow allowfullscreen allowpaymentrequest alt async autocomplete autofocus autoplay
                            bgcolor border buffered
                            challenge charset checked cite code codebase color cols colspan content contenteditable contextmenu controls coords crossorigin
                            data datetime decoding defer dir dirname disabled download draggable dropzone 
                            enctype enterkeyhint 
                            form formaction formenctype formmethod formnovalidate formtarget
                            headers height hidden high href hreflang
                            icon id importance intrinsicsize inputmode integrity is
                            keytype kind
                            label lang list loading longdesc loop low
                            manifest max maxlength media method min minlength multiple muted
                            name novalidate
                            open optimum
                            pattern ping placeholder poster preload
                            readonly referrerpolicy rel required reversed rows rowspan
                            sandbox scope scoped selected shape size sizes slot span spellcheck src srcdoc srclang srcset start step style summary
                            tabindex target title translate type
                            usemap
                            value width wrap)