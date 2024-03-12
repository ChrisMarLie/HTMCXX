#ifndef __HTMCXX_HTML_TAG__
#define __HTMCXX_HTML_TAG__

#include <algorithm>
#include <concepts>
#include <initializer_list>
#include <memory>
#include <string>
#include <ranges>
#include <type_traits>
#include <vector>

#include "itag.h"

#include <iostream>

namespace htmcxx::tags
{
    template <class T>
    concept Tag = std::derived_from<T, htmcxx::tags::itag>;

    template <class Derived, Attribute... T>
    class html_tag : public itag
    {
    public:

        /*========================= Copies && Moves =========================*/

        html_tag(const html_tag &other) { *this = other; }

        //---------------------------------------------------------------

        html_tag &operator=(const html_tag &other)
        {
            *this = std::move(*dynamic_cast<Derived*>(other.clone().get()));
            return *this;
        }

        //---------------------------------------------------------------

        html_tag &operator=(html_tag &&) = default;

        //---------------------------------------------------------------

        html_tag(html_tag &&) = default;

        /*========================= Ctor && Dtor =========================*/

        virtual ~html_tag() override = default;

        //---------------------------------------------------------------

        inline html_tag(T &&...attributes)
        {
            (attributes_.emplace_back(std::make_unique<T>(std::forward<T>(attributes))), ...);
        }

        /*========================= Operators Override =========================*/

        template <Tag... U>
        inline Derived &operator()(U&& ...elements)
        {
            (subelements_.emplace_back(std::make_unique<U>(std::move(elements))), ...);
            return *dynamic_cast<Derived*>(this);
        }

        //---------------------------------------------------------------

        template <Tag... U>
        inline Derived &operator()(const U& ...elements)
        {
            (subelements_.emplace_back(std::make_unique<U>(elements)), ...);
            return *dynamic_cast<Derived*>(this);
        }

        //---------------------------------------------------------------

        template <Tag U>
        inline Derived& operator <<(U &&element)
        {
            subelements_.emplace_back(std::make_unique<U>(std::move(element)));
            return *dynamic_cast<Derived*>(this);
        }

        //---------------------------------------------------------------

        template <Tag U>
        inline Derived& operator <<(const U &element)
        {
            subelements_.emplace_back(std::make_unique<U>(element));
            return *dynamic_cast<Derived*>(this);
        }

        //---------------------------------------------------------------

        template <Attribute U>
        inline Derived& operator +(U &&attribute)
        {
            subelements_.emplace_back(std::make_unique<U>(std::move(attribute)));
            return *dynamic_cast<Derived*>(this);
        }

        //---------------------------------------------------------------

        template <Attribute U>
        inline Derived& operator +(const U &attribute)
        {
            attributes_.emplace_back(std::make_unique<U>(attribute));
            return *dynamic_cast<Derived*>(this);
        }
   
        /*========================= Other methods =========================*/

        inline explicit operator std::string() const override
        {
            std::string formatted = std::format("{}<{}", tabulation_, tag_name());

            for (const auto &[index, attr_ptr] : attributes_ | std::views::enumerate)
            {
                formatted += " " +  static_cast<std::string>(*attr_ptr);
            }

            formatted += ">\n";

            for (auto &elem_ptr : subelements_)
            {
                elem_ptr->tabulation_ = this->tabulation_ + "\t";
                formatted += static_cast<std::string>(*elem_ptr);
            }

            formatted += std::format("{}</{}>\n", tabulation_, tag_name());

            return formatted;
        }

        //---------------------------------------------------------------

        inline bool has_elements() const { return not subelements_.empty(); }

        //---------------------------------------------------------------

        inline bool has_attributes() const { return not attributes_.empty(); }

        //---------------------------------------------------------------

        template <Tag U>
        inline U &get()
        {
            //Find tag with the same name, attributes don't care
            auto it = std::ranges::find_if(subelements_, 
                [&](const std::unique_ptr<tags::itag> &elem_ptr) { return utils::instanceof<U>(elem_ptr); });

            if(it == subelements_.end())
            {
                throw std::out_of_range(std::format("Element not found in <{}>", this->tag_name()));
            }

            return *dynamic_cast<U*>(it->get());
        }

    protected:
        
        std::vector<std::unique_ptr<attributes::iattribute>> attributes_;

        std::vector<std::unique_ptr<tags::itag>> subelements_;

    private:
        virtual inline Derived* get_type()
        {
            std::cout << typeid(*this).name() << std::endl;
            return dynamic_cast<Derived*>(this);
        }

        inline html_tag(const std::vector<std::unique_ptr<attributes::iattribute>> &attributes) 
        {
            std::ranges::for_each(attributes, 
                    [this](const auto &attr_ptr) { attributes_.emplace_back(attr_ptr->clone()); });
        }

        //---------------------------------------------------------------

        inline std::unique_ptr<itag> clone() const override
        {
            std::unique_ptr<html_tag> copy(new Derived(attributes_));

            std::ranges::for_each(subelements_, 
                    [&copy](const auto &elem_ptr) { copy->subelements_.emplace_back(elem_ptr->clone()); });

            return copy;
        }
    };



    /*-------- Not generated classes because of his name or other considerations ----------*/

    template <Attribute... T>
    class template_name : public html_tag<template_name<T...>, T...>
    {
    public:      
        template_name &operator=(const template_name &) = default;
        template_name(const template_name &) = default;

        template_name &operator=(template_name &&) = default;
        template_name(template_name &&) = default;

        template_name(T &&...attributes_) : html_tag<template_name<T...>, T...>(std::forward<T>(attributes_)...) {}
        ~template_name() override = default;

        using html_tag<template_name<T...>, T...>::html_tag;

        std::string tag_name() const override { return "template"; }
    };

    //----------------------------------------------------------------------------------

    /**
     * @brief This class is used to wrap HTML elements that are not associated with a specific tag.
     *        It formats their children in columns.
     * 
     * @note Since it's just a wrapper, it CANNOT hold attributes.
     */
    template <Attribute... T>
    class box : public html_tag<box<T...>, T...>
    {
    public:    
        box &operator=(const box &) = default;
        box(const box &) = default;

        box &operator=(box &&) = default;
        box(box &&) = default;

        box() : html_tag<box<T...>, T...>() {}
        ~box() override = default;

        using html_tag<box<T...>, T...>::html_tag;

        inline explicit operator std::string() const override
        {
            return std::ranges::fold_left(this->subelements_, "", 
                        [](const std::string &acc, const std::unique_ptr<itag> &subelement) { 
                            return acc + static_cast<std::string>(*subelement) + "\n"; 
                        });
        }
    };

    //----------------------------------------------------------------------------------

    class text : public itag
    {
    public:   
        text &operator=(const text &) = default;
        text(const text &) = default;

        text &operator=(text &&) = default;
        text(text &&) = default;

        text(const std::string &value) : value_{value} {}
        ~text() override = default;

        inline explicit operator std::string() const override
        {
            return this->tabulation_ + value_ + "\n";
        }

        inline std::unique_ptr<itag> clone() const override
        {
            return std::make_unique<text>(this->value_);
        }

    private:
        std::string value_;
    };

    class doctype : public text
    {
    public:   
        doctype &operator=(const doctype &) = default;
        doctype(const doctype &) = default;

        doctype &operator=(doctype &&) = default;
        doctype(doctype &&) = default;

        doctype() : text("<!DOCTYPE html>") {}
        ~doctype() override = default;
    };

    template <Attribute... T>
    class meta : public html_tag<meta<T...>, T...>
    {
    public:
        meta &operator=(const meta &) = default;
        meta(const meta &) = default;

        meta &operator=(meta &&) = default;
        meta(meta &&) = default;

        using html_tag<meta<T...>, T...>::html_tag;
        
        meta(T &&...attributes_) : html_tag<meta<T...>, T...>(std::forward<T>(attributes_)...) {}
        ~meta() override = default;
    
        inline explicit operator std::string() const override
        {
            std::string formatted = std::format("{}<{}", this->tabulation_, this->tag_name());

            for (const auto &[index, attr_ptr] : this->attributes_ | std::views::enumerate)
            {
                formatted += " " +  static_cast<std::string>(*attr_ptr);
            }

            formatted += ">\n";

            return formatted;
        }
    };

} //namespace htmcxx::tags

#endif //__HTMCXX_HTML_ELEMENT__