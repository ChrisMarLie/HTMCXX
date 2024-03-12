#include "htmcxx/tags/tags.h" 
#include "htmcxx/tags/prebuilds.h"
#include <fstream>

namespace att = htmcxx::attributes;
namespace tag = htmcxx::tags;


auto main() -> int
{
    // Create new index html file
    std::ofstream index_html("index.html");

    /*
    *  Create custom html element equivalent to:
    *    <section id="hello-world-container">
    *           <p style="color: red;"> Hello World! </p>
    *    </section>
    */
    auto content =  tag::section{att::id("hello-world-container")}
                    (
                        tag::p{att::style("color: red;")}(tag::text("Hello World!"))
                    );


    // Add content to file
    index_html << (std::string)content;

    return 0;
}