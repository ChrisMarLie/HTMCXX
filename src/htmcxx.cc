export module htmcxx;

export import :tags.generated;
export import :attributes.generated;

export namespace htmcxx
{
    const tags::box HTML5 =
        tags::box{}
        (
            tags::doctype{},
            tags::html{attributes::lang("en")}
            (
                tags::head{}
                (
                    tags::meta{attributes::charset("UTF-8")},
                    tags::meta{attributes::name("viewport"), attributes::content("width=device-width, initial-scale=1.0")},
                    tags::title{}
                ),
                tags::body{}
            )
        );
}