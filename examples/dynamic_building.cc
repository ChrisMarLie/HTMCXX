#include "htmcxx/tags/tags.h" 
#include "htmcxx/tags/prebuilds.h"
#include <fstream>
#include <iostream>

namespace att = htmcxx::attributes;
namespace tag = htmcxx::tags;


auto main() -> int
{
    //Open new html file
    std::ofstream index_html("index.html");

    //Create a ul, and add every value from list of values
    tag::ul list{};
    for(auto fruit : {"orange", "apple", "banana", "cherry", "strawberry"})
    {
        list << tag::li{att::style("font-size: 50px;")}(tag::text(fruit));
    }
    
    // Copy content of prebuilding HTML5 template
    auto content = tag::prebuilds::HTML5;

    // Add list into body tag
    content.get<tag::html<att::lang>>().get<tag::body<>>() << std::move(list);

    // Add content to file
    index_html << (std::string)content;

    return 0;
}