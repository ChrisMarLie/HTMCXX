#ifndef __HTMCXX_IATTRIBUTE__
#define __HTMCXX_IATTRIBUTE__

#include <string>

namespace htmcxx::attributes
{  
    class iattribute
    {   
        public:
            virtual ~iattribute() = default;
            virtual operator std::string() const = 0;
            virtual std::unique_ptr<iattribute> clone() const = 0;

        protected:
            iattribute(const std::string &value) : value_{value} {}

            const std::string value_;
    };

} //namespace htmcxx::attributes

#endif //__HTMCXX_IATTRIBUTE__