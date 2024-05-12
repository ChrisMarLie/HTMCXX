#ifndef __HTMCXX_HTML_ATTRIBUTE__
#define __HTMCXX_HTML_ATTRIBUTE__

#include <format>
#include <iomanip>
#include <iostream>
#include <string>
#include "htmcxx/utils.h"
#include "htmcxx/attributes/iattribute.h"

namespace htmcxx::attributes
{

    template <class Derived>
    class html_attribute : public iattribute
    {
    public:
        /*========================= Copies && Moves =========================*/

        html_attribute &operator=(html_attribute&&) = default;

        //---------------------------------------------------------------

        html_attribute &operator=(const html_attribute&) = default;

        //---------------------------------------------------------------

        html_attribute(html_attribute&&) = default;

        //---------------------------------------------------------------

        html_attribute(const html_attribute&) = default;


        /*========================= Ctor && Dtor =========================*/

        inline html_attribute(const std::string &value) : value_{value} {}

        //---------------------------------------------------------------

        inline explicit operator std::string() const override
        {
            return std::format(R"({}="{}")", htmcxx::utils::get_class_name(*this), value_);
        }

        //---------------------------------------------------------------

        inline std::unique_ptr<iattribute> clone() const override
        {
            return std::make_unique<Derived>(this->value_);
        }

        //---------------------------------------------------------------

        bool has_value() const { return not value_.empty(); }

    protected:
        std::string value_;
    };

    /*-------- Not auto-generated classes because of his name or other considerations ----------*/

    class class_name : public html_attribute<class_name>
    {
    public:
        class_name(const std::string &value) : html_attribute{value} {}

        inline explicit operator std::string() const override
        {
            return std::format("class=\"{}\"", value_);
        }
    };

    //----------------------------------------------------------------------------------

    class default_name : public html_attribute<default_name>
    {
    public:
        default_name(const std::string &value) : html_attribute{value} {}

        inline explicit operator std::string() const override
        {
            return std::format("default=\"{}\"", value_);
        }
    };

    //----------------------------------------------------------------------------------

    class for_name : public html_attribute<for_name>
    {
    public:
        for_name(const std::string &value) : html_attribute{value} {}

        inline explicit operator std::string() const override
        {
            return std::format("for=\"{}\"", value_);
        }
    };

} // namespace htmcxx::attributes

#endif //__HTMCXX_HTML_ATTRIBUTE__