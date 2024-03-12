#ifndef __HTMCXX_PREBUILDS__
#define __HTMCXX_PREBUILDS__

#include "htmcxx/tags/tags.h"
#include "htmcxx/attributes/attributes.h"

namespace htmcxx::tags::prebuilds
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

#endif //__HTMCXX_PREBUILDS__