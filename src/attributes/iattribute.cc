module;

#include <string>
#include <memory>

export module htmcxx:attributes.interface;

export namespace htmcxx::attributes
{
    class iattribute
    {
    public:
        virtual ~iattribute() = default;

        virtual explicit operator std::string() const = 0;

        virtual std::unique_ptr<iattribute> clone() const = 0;
    };

} // namespace htmcxx::attributes
