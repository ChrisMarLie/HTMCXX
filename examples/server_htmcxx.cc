#include "crow.h"
#include "htmcxx.h"
#include <ranges>
#include <vector>

using namespace htmcxx;
using namespace htmcxx::tags;

const auto card_style = attributes::style(
    "background-color: #fff;"
    "border-radius: 8px;"
    "box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);"
    "width: 150px;"
    "height: 180px;" 
    "text-align: center;"
);

const auto list_style = attributes::style(
    "list-style-type: none;"
    "display:flex;"
    "gap: 10px;"
    "flex-direction: row;"
);

const auto HTML_FOLLOWERS = [](const std::vector<std::string> &followers) {
    auto HTML5 = prebuilds::HTML5;

    return (
        HTML5.get<html>().get<body>()
        (
            p{attributes::style("font-weight: bold;")}( "Followers "),
            ul{list_style}
            (
                followers | std::views::transform([](auto &follower) { return li{card_style}(follower); })
            )  
        )
    );
};

auto main() -> int
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([] {
        return HTML_FOLLOWERS(
            { "James", "Emily", "William", "Olivia",  "Benjamin", "Charlotte", "Samuel", "Grace" }
        );
    });


    app.port(8080).run();

    return 0;
}