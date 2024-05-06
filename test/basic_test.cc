#include <gtest/gtest.h>
#include <type_traits>
#include "htmcxx/attributes/attributes.h" 
#include "htmcxx/tags/prebuilds.h"
#include "htmcxx/tags/tags.h" 

namespace attr = htmcxx::attributes;
namespace tag = htmcxx::tags;

TEST(Tag, AddDynamicallyAttributeMovement) 
{
  tag::div tag;
  ASSERT_FALSE(tag.has_attributes());
  ASSERT_EQ(tag.num_attributes(), 0);

  attr::class_name class_name("any-class");
  tag << attr::id("any-id") << std::move(class_name);

  ASSERT_TRUE(tag.has_attributes());
  ASSERT_EQ(tag.num_attributes(), 2);
  ASSERT_FALSE(class_name.has_value());
}

TEST(Tag, AddDynamicallyAttributeCopy) 
{
  tag::div tag;
  
  ASSERT_FALSE(tag.has_attributes());
  ASSERT_EQ(tag.num_attributes(), 0);

  attr::style style("any: style");
  tag << style;

  ASSERT_EQ(tag.num_attributes(), 1);
  ASSERT_TRUE(style.has_value());
}

TEST(Tag, AddDynamicallyTagMovement)
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

TEST(Tag, AddDynamicallyTagCopy) 
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

TEST(Tag, AddString)
{
  auto paragraph = tag::p{}("Hello");
  ASSERT_EQ(paragraph.num_elements(), 1);
  ASSERT_EQ((std::string)paragraph.get<tag::text>(), "Hello\n");

  std::string text = "World";
  auto paragraph2 = tag::p{}(text);
  ASSERT_EQ(paragraph2.num_elements(), 1);
  ASSERT_EQ((std::string)paragraph2.get<tag::text>(), text + "\n");

  auto paragraph3 = tag::p{}(std::move(text));
  ASSERT_EQ(paragraph3.num_elements(), 1);
  ASSERT_TRUE(text.empty());
  ASSERT_EQ((std::string)paragraph3.get<tag::text>(), "World\n");
}

TEST(Tag, GetTag) 
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
  tag.get<tag::html>() << attr::style("any: style");
  ASSERT_EQ(tag.get<tag::html>().num_attributes(), 1);
}

TEST(Tag, GetAttribute) 
{
  auto tag = tag::div{attr::style("any: style"), attr::id("any-id")};

  ASSERT_EQ(typeid(tag.get<attr::style>()), typeid(attr::style));
  ASSERT_THROW(tag.get<attr::lang>(), std::out_of_range);
}

TEST(Tag, Clear)
{
  auto tag = tag::box{attr::id("any-id"), attr::lang("any"), attr::class_name("any")}
             (
                tag::div{},
                tag::button{},
                tag::p{}
             );

  ASSERT_TRUE(tag.has_attributes());
  tag.clear_attributes();
  ASSERT_FALSE(tag.has_attributes());

  ASSERT_TRUE(tag.has_elements());
  tag.clear_elements();
  ASSERT_FALSE(tag.has_elements());
}

TEST(Tag, RemoveAll)
{
  auto tag = tag::box{attr::id("any-id"), attr::lang("any"), attr::class_name("any")}
             (
                tag::div{},
                tag::button{},
                tag::p{},
                tag::div{}
             );

  ASSERT_EQ(tag.num_attributes(), 3);
  ASSERT_EQ(tag.remove_all<attr::lang>(), 1);
  ASSERT_EQ(tag.num_attributes(), 2);
  
  ASSERT_EQ(tag.num_elements(), 4);
  ASSERT_EQ(tag.remove_all<tag::div>(), 2);
  ASSERT_EQ(tag.num_elements(), 2);
}
