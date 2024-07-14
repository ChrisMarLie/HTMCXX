#ifndef __HTMCXX_PREBUILDS__
#define __HTMCXX_PREBUILDS__

#include "htmcxx/tags/tags.h"
#include "htmcxx/attributes/attributes.h"

/** @file prebuilds.h
 *  @brief Ready-made tags and attributes to aid in the development process
 */

namespace htmcxx::tags::prebuilds
{
    /**
     * @brief Prebuild HTML5 template with head, body, and empty title.
     */
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