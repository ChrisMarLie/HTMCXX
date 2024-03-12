#ifndef __HTMCXX_HTML_ATTRIBUTE__
#define __HTMCXX_HTML_ATTRIBUTE__

#include <format>
#include <iomanip>
#include <string>

#include "htmcxx/utils.h"
#include "iattribute.h"

namespace htmcxx::attributes
{  
    template <class Derived>
    class html_attribute : public iattribute
    {   
        public:
            ~html_attribute() override = default;

            inline operator std::string() const override
            {
                return std::format(R"({}="{}")", htmcxx::utils::get_class_name(*this), value_);
            }

            inline std::unique_ptr<iattribute> clone() const override 
            { 
                return std::make_unique<Derived>(this->value_);
            }

        protected:
            inline html_attribute(const std::string &value) : iattribute{value} {}
    };

    /*-------- Not auto-generated classes because of his name or other considerations ----------*/

    class class_name : public html_attribute<class_name>
    {
    public:
        class_name(const std::string &value) : html_attribute{value} {}
        ~class_name() override = default;

        inline operator std::string() const override
        {
            return std::format("class=\"{}\"", value_);
        }
    };

    //----------------------------------------------------------------------------------

    class default_name : public html_attribute<default_name>
    {
    public:
        default_name(const std::string &value) : html_attribute{value} {}
        ~default_name() override = default;

        inline operator std::string() const override
        {
            return std::format("default=\"{}\"", value_);
        }
    };

    //----------------------------------------------------------------------------------

    class for_name : public html_attribute<for_name>
    {
    public:
        for_name(const std::string &value) : html_attribute{value} {}
        ~for_name() override = default;

        inline operator std::string() const override
        {
            return std::format("for=\"{}\"", value_);
        }
    };
    
} // namespace htmcxx::attributes

#endif //__HTMCXX_HTML_ATTRIBUTE__