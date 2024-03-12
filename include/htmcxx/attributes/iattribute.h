#ifndef __HTMCXX_IATTRIBUTE__
#define __HTMCXX_IATTRIBUTE__

#include <string>

namespace htmcxx::attributes
{
    class iattribute
    {
    public:
        virtual ~iattribute() = default;

        virtual explicit operator std::string() const = 0;

        virtual std::unique_ptr<iattribute> clone() const = 0;
    };

} // namespace htmcxx::attributes

#endif //__HTMCXX_IATTRIBUTE__