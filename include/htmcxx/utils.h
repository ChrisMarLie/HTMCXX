#ifndef __HTMCXX_UTILS__
#define __HTMCXX_UTILS__

#include <nameof.hpp>
#include <memory>
#include <ranges>
#include <string>

namespace htmcxx::utils
{   
    template<class T>
    std::string get_class_name([[maybe_unused]]const T &object)
    { 
        
        return std::string(NAMEOF_SHORT_TYPE_RTTI(object));
    }

    template<typename Base, typename T>
    inline bool instanceof(const std::unique_ptr<T> &ptr) {
        return dynamic_cast<const Base*>(ptr.get()) != nullptr;
    }
    
} //namespace htmcxx::utils

#endif //__HTMCXX_UTILS__