#include <gtest/gtest.h>
#include <type_traits>
#include "htmcxx/attributes/attributes.h" 
#include "htmcxx/tags/prebuilds.h"
#include "htmcxx/tags/tags.h" 

namespace attr = htmcxx::attributes;
namespace tag = htmcxx::tags;

TEST(HTMCXX, AddDynamicallyAttributeMovement) 
{
  tag::div tag;
  ASSERT_FALSE(tag.has_attributes());
  ASSERT_EQ(tag.num_attributes(), 0);

  attr::class_name class_name("any-class");
  tag + attr::id("any-id") + std::move(class_name);

  ASSERT_TRUE(tag.has_attributes());
  ASSERT_EQ(tag.num_attributes(), 2);
  ASSERT_FALSE(class_name.has_value());
}

TEST(HTMCXX, AddDynamicallyAttributeCopy) 
{
  tag::div tag;
  
  ASSERT_FALSE(tag.has_attributes());
  ASSERT_EQ(tag.num_attributes(), 0);

  attr::style style("any: style");
  tag + style;

  ASSERT_EQ(tag.num_attributes(), 1);
  ASSERT_TRUE(style.has_value());
}

TEST(HTMCXX, AddDynamicallyTagMovement)
{
  tag::div tag;

  ASSERT_FALSE(tag.has_elements());
  ASSERT_EQ(tag.num_elements(), 0);

  tag::button button{attr::id("any-id")};
  button(tag::p{});
  tag << tag::p{} << std::move(button);

  ASSERT_EQ(tag.num_elements(), 2);
  ASSERT_TRUE(tag.has_elements());
  ASSERT_FALSE(button.has_elements());
  ASSERT_FALSE(button.has_attributes());
}

TEST(HTMCXX, AddDynamicallyTagCopy) 
{
  tag::div tag;

  ASSERT_FALSE(tag.has_elements());
  ASSERT_EQ(tag.num_elements(), 0);

  tag::div div{attr::id("any-id")};
  div(tag::p{});
  tag << div;

  ASSERT_EQ(tag.num_elements(), 1);
  ASSERT_TRUE(tag.has_elements());
  ASSERT_TRUE(div.has_attributes());
  ASSERT_TRUE(div.has_elements());
}

TEST(HTMCXX, GetTag) 
{
  auto tag =  tag::box{}
              (
                tag::html{}
                (
                  tag::div{},
                  tag::div{}
                )
              );

  ASSERT_EQ(typeid(tag.get<tag::html>()), typeid(tag::html));
  ASSERT_EQ(typeid(tag.get<tag::html>().get<tag::div>()), typeid(tag::div));
  ASSERT_THROW(tag.get<tag::div>(), std::out_of_range);
  
  ASSERT_EQ(tag.get<tag::html>().num_attributes(), 0);
  tag.get<tag::html>() + attr::style("any: style");
  ASSERT_EQ(tag.get<tag::html>().num_attributes(), 1);
}

TEST(HTMCXX, GetAttribute) 
{
  auto tag = tag::div{attr::style("any: style"), attr::id("any-id")};

  ASSERT_EQ(typeid(tag.get<attr::style>()), typeid(attr::style));
  ASSERT_THROW(tag.get<attr::lang>(), std::out_of_range);
}
