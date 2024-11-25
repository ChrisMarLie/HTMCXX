#include <fstream>
#include "htmcxx.h" 

using namespace htmcxx;
using namespace htmcxx::tags;


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
    auto content =  section{attributes::id("hello-world-container")}
                    (
                        p{attributes::style("color: red;")}
                        (
                            "Hello World!"
                        )
                    );


    // Add content to file
    index_html << (std::string)content;

    return 0;
}