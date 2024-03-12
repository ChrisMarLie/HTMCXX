#ifndef __HTMCXX_HTML_TAG__
#define __HTMCXX_HTML_TAG__

#include <algorithm>
#include <format>
#include <initializer_list>
#include <memory>
#include <string>
#include <ranges>
#include <vector>
#include "htmcxx/tags/itag.h"
#include "htmcxx/attributes/iattribute.h"

namespace htmcxx::tags
{

    /**
     * @brief Generic HTML element without any specific semantic meaning.
     *
     * @note Most HTML tags will inherit from this.
     */
    template <class Derived>
    class html_tag : public itag
    {
    public:
        /*========================= Copies && Moves =========================*/

        html_tag &operator=(const html_tag &other)
        {
            *this = std::move(*dynamic_cast<Derived *>(other.clone().get()));
            return *this;
        }

        //---------------------------------------------------------------

        html_tag &operator=(html_tag &&) = default;

        /*========================= Ctor && Dtor =========================*/

        html_tag(html_tag &&) = default;

        //---------------------------------------------------------------

        inline html_tag(const html_tag &other) { *this = other; }

        //---------------------------------------------------------------

        /**
         * @brief Constructs an HTML element with different attributes.
         *
         * @tparam T Parameter pack representing the types of the attributes.
         * @param attributes Attributes to be added to the HTML element.
         */
        template <class... T>
        inline html_tag(T &&...attributes)
        {
            (attributes_.emplace_back(std::make_unique<std::decay_t<T>>(std::forward<T>(attributes))), ...);
        }

        /*========================= Operators Override =========================*/

        /**
         * @brief Adds multiple nested tags to the current element.
         *
         * @tparam T Parameter pack representing the types of the nested tags to add.
         * @param elements The nested tags to add to the current element.
         * @return A reference to the modified element after adding the nested tags.
         *
         */
        template <class... T>
        inline Derived &operator()(T &&...elements) noexcept
        {
            (subelements_.emplace_back(std::make_unique<std::decay_t<T>>(std::forward<T>(elements))), ...);
            return get_type();
        }

        //---------------------------------------------------------------

        /**
         * @brief Adds a nested tag to the current element.
         *
         * @tparam T The type of the nested tag to add.
         * @param element The nested tag to add to the current element.
         * @return A reference to the modified element after adding the nested tag.
         *
         */
        template <class T>
        inline Derived &operator<<(T &&element) noexcept
        {
            subelements_.emplace_back(std::make_unique<std::decay_t<T>>(std::forward<T>(element)));
            return get_type();
        }

        //---------------------------------------------------------------

        /**
         * @brief Adds a new attribute to the current tag.
         *
         * @tparam T The type of the attribute to add.
         * @param attribute The attribute value to add to the tag.
         * @return A reference to the modified tag after adding the attribute.
         *
         */
        template <class T>
        inline Derived &operator+(T &&attribute) noexcept
        {
            attributes_.emplace_back(std::make_unique<std::decay_t<T>>(std::forward<T>(attribute)));
            return get_type();
        }

        /*========================= Other methods =========================*/

        /**
         * @brief Format this element as HTML structure and converts it into a string.
         */
        inline explicit operator std::string() const override
        {
            std::string formatted = std::format("{}<{}", tabulation_, tag_name());

            for (const auto &attr_ptr : attributes_)
            {
                formatted += " " + static_cast<std::string>(*attr_ptr);
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

        /**
         * @brief Check if current tag has nested tags
         *
         * @returns True if it has nested tags
         */
        inline bool has_elements() const noexcept { return not subelements_.empty(); }

        //---------------------------------------------------------------

        /**
         * @brief Get number of nested elements.
         *
         * @returns Number of elements.
         */
        constexpr inline size_t num_elements() const noexcept { return subelements_.size(); }

        //---------------------------------------------------------------

        /**
         * @brief Check if current tag has attributes
         *
         * @returns True if it has attributes.
         */
        constexpr inline bool has_attributes() const noexcept { return not attributes_.empty(); }

        //---------------------------------------------------------------

        /**
         * @brief Get number of attributes.
         *
         * @returns Number of attributes.
         */
        constexpr inline size_t num_attributes() const noexcept { return attributes_.size(); }

        //---------------------------------------------------------------

        /**
         * @brief Returns a reference to the first appearance of the nested HTML tag or attribute within the current tag.
         *
         * @tparam T The type of the HTML tag or attribute to search for.
         * @return Reference to the nested HTML tag or attribute.
         *
         * @throws std::out_of_range if the nested tag or attribute does not exist within the current tag.
         */
        template <class T>
        inline T &get()
        {
            T* searched_type = nullptr;
            std::string error_msg;
            constexpr auto fn_to_search = [](const auto &ptr){ return utils::instanceof<T>(ptr); };
            
            if constexpr (std::derived_from<T, tags::itag>)
            {
                auto it = std::ranges::find_if(subelements_, fn_to_search);

                if(it != subelements_.end())
                    searched_type = dynamic_cast<T*>(it->get());
                else
                    error_msg = std::format("Tag <{}> was not found in <{}>", T().tag_name(), this->tag_name());
            }
            else
            {
                auto it = std::ranges::find_if(attributes_, fn_to_search);
                
                if(it != attributes_.end())
                    searched_type = dynamic_cast<T*>(it->get());
                else
                    error_msg = std::format("Attribute \"{}\" was not found in <{}>",  htmcxx::utils::get_class_name(T("")), this->tag_name());
            }
            
            return searched_type? *searched_type : throw std::out_of_range(error_msg);
        }

    protected:
        //---------------------------------------------------------------

        inline html_tag(const std::vector<std::unique_ptr<attributes::iattribute>> &attributes)
        {
            std::ranges::for_each(attributes,
                                  [this](const auto &attr_ptr)
                                  { attributes_.emplace_back(attr_ptr->clone()); });
        }

        //---------------------------------------------------------------

        inline Derived &get_type() noexcept
        {
            return *dynamic_cast<Derived *>(this);
        }

        //---------------------------------------------------------------

        inline std::unique_ptr<itag> clone() const override
        {
            std::unique_ptr<html_tag> copy(new Derived(attributes_));

            std::ranges::for_each(subelements_,
                                  [&copy](const auto &elem_ptr)
                                  { copy->subelements_.emplace_back(elem_ptr->clone()); });

            return copy;
        }

        //---------------------------------------------------------------

        std::vector<std::unique_ptr<attributes::iattribute>> attributes_;

        std::vector<std::unique_ptr<tags::itag>> subelements_;
    };

    /*-------- Not generated classes because of his name or other considerations ----------*/

    class template_name final : public html_tag<template_name>
    {
    public:
        using html_tag<template_name>::html_tag;

        std::string tag_name() const override { return "template"; }
    };

    //----------------------------------------------------------------------------------

    /**
     * @brief This class is used to wrap HTML elements that are not associated with a specific tag.
     *        It formats their children in columns.
     *
     * @note Since it's just a wrapper, it CANNOT hold attributes.
     */
    class box final : public html_tag<box>
    {
    public:
        using html_tag<box>::html_tag;

        inline explicit operator std::string() const override
        {
            return std::ranges::fold_left(this->subelements_, "",
                                          [](const std::string &acc, const std::unique_ptr<itag> &subelement)
                                          {
                                              return acc + static_cast<std::string>(*subelement) + "\n";
                                          });
        }
    };

    //----------------------------------------------------------------------------------

    class meta final : public html_tag<meta>
    {
    public:
        using html_tag<meta>::html_tag;

        inline explicit operator std::string() const override
        {
            std::string formatted = std::format("{}<{}", this->tabulation_, this->tag_name());

            for (const auto &attr_ptr : this->attributes_)
            {
                formatted += " " + static_cast<std::string>(*attr_ptr);
            }

            formatted += ">\n";

            return formatted;
        }
    };

    //----------------------------------------------------------------------------------

    /**
     * @brief Represents plain text for HTML.
     *
     * @note This class is intended to be used in conjunction with other HTML
     * elements to represent text content within an HTML document.
     */
    class text : public itag
    {
    public:
        text(const std::string &value) : value_{value} {}

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

    //----------------------------------------------------------------------------------

    class doctype final : public text
    {
    public:
        doctype() : text("<!DOCTYPE html>") {}
    };

} // namespace htmcxx::tags

#endif //__HTMCXX_HTML_ELEMENT__