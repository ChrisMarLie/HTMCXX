#ifndef __HTMCXX_UTILS__
#define __HTMCXX_UTILS__

#include <cxxabi.h>
#include <memory>
#include <ranges>
#include <string>

namespace htmcxx::utils
{   
    template<class T>
    std::string get_class_name(const T &object)
    { 
        char* class_with_namespace = abi::__cxa_demangle(typeid(object).name(), 0, 0, 0);

        auto class_name = std::string(class_with_namespace) | std::views::take_while([](const char& c){ return c != '<';})
                                                            | std::views::reverse 
                                                            | std::views::take_while([](const char& c){ return c != ':';}) 
                                                            | std::views::reverse;

        std::free(class_with_namespace);

        return std::string(std::make_move_iterator(class_name.begin()), std::make_move_iterator(class_name.end()));     
    }

    template<typename Base, typename T>
    inline bool instanceof(const std::unique_ptr<T> &ptr) {
        return dynamic_cast<const Base*>(ptr.get()) != nullptr;
    }
    
} //namespace htmcxx::utils

#endif //__HTMCXX_UTILS__