#ifndef __HTMCXX_ITAG__
#define __HTMCXX_ITAG__

#include <string>

#include "htmcxx/attributes/attributes.h"
#include "htmcxx/utils.h"

namespace htmcxx::tags
{
    template <class T>
    concept Attribute = std::derived_from<T, htmcxx::attributes::iattribute>;

    class itag
    {
    public:      
        virtual ~itag() = default;
        virtual operator std::string() const = 0;

        template <class Derived, Attribute... T>
        friend class html_tag;

    protected: 

        virtual std::string tag_name() const { return utils::get_class_name(*this); } 
        std::string tabulation_;

    private:
    
        virtual std::unique_ptr<itag> clone() const = 0;
    };

} //namespace htmcxx::tags

#endif //__HTMCXX_ITAG__