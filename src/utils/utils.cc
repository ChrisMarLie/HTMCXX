module;

#include <nameof.hpp>
#include <memory>
#include <ranges>
#include <string>

export module htmcxx:utils;

export namespace htmcxx::utils
{   
    template<class T>
    std::string get_class_name([[maybe_unused]] const T &object)
    { 
        
        return std::string(NAMEOF_SHORT_TYPE_RTTI(object));
    }

    template<typename Base, typename T>
    inline bool instanceof(const std::unique_ptr<T> &ptr) 
    {
        return dynamic_cast<const Base*>(ptr.get()) != nullptr;
    }
    
} //namespace htmcxx::utils