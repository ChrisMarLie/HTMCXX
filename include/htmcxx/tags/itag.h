#ifndef __HTMCXX_ITAG__
#define __HTMCXX_ITAG__

#include <string>
#include "htmcxx/utils.h"

namespace htmcxx::tags
{

    class itag
    {
    public:
        template <class Derived>
        friend class html_tag;

        virtual ~itag() = default;

        virtual operator std::string() const = 0;

        inline virtual std::string tag_name() const { return utils::get_class_name(*this); }

    protected:
        virtual std::unique_ptr<itag> clone() const = 0;

        std::string tabulation_;
    };

} // namespace htmcxx::tags

#endif //__HTMCXX_ITAG__