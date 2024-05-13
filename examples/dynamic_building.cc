#include <fstream>

import htmcxx;

namespace attr = htmcxx::attributes;
namespace tag = htmcxx::tags;


auto main() -> int
{
    //Open new html file
    std::ofstream index_html("index.html");

    //Create an ul, and add every value from list of values
    tag::ul fruit_list;
    for(auto fruit : {"orange", "apple", "banana", "cherry", "strawberry"})
    {   
        //Create new li with the fruit name inside
        tag::li list_item = tag::li{attr::style("font-size: 50px;")}
                            (
                                fruit
                            );

        //Finally move it into the list
        fruit_list << std::move(list_item);
    }
    
    // Copy content of prebuilding HTML5 template
    auto content = htmcxx::HTML5;

    // Add list into body tag
    content.get<tag::html>().get<tag::body>() << std::move(fruit_list);

    // Add content to file
    index_html << (std::string)content;

    return 0;
}