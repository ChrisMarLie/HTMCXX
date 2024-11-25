#include <fstream>
#include "htmcxx.h"

using namespace htmcxx;
using namespace htmcxx::tags;

auto main() -> int
{
    //Open new html file
    std::ofstream index_html("index.html");

    //Create an ul, and add every value from list of values
    ul fruit_list;
    for(auto fruit : {"orange", "apple", "banana", "cherry", "strawberry"})
    {   
        //Create new li with the fruit name inside
        li list_item = li{attributes::style("font-size: 50px;")}
                        (
                            fruit
                        );

        //Finally move it into the list
        fruit_list << std::move(list_item);
    }
    
    // Copy content of prebuilding HTML5 template
    auto content = prebuilds::HTML5;

    // Add list into body tag
    content.get<html>().get<body>() << std::move(fruit_list);

    // Add content to file
    index_html << (std::string)content;

    return 0;
}