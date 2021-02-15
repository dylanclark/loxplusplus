#include <loxpp_pch.h>

#include <Object.h>
#include <VisitHelpers.h>

namespace Loxpp::Object {

// Handy template class and function to cast from a variant T1 to variant T2,
// where T2 is a superset of T1: https://stackoverflow.com/a/47204507/15150338
template <class... Args> struct variant_cast_proxy {
    std::variant<Args...> v;

    template <class... ToArgs> operator std::variant<ToArgs...>() const {
        return std::visit(
            [](auto&& arg) -> std::variant<ToArgs...> { return arg; }, v);
    }
};

template <class... Args>
auto variant_cast(const std::variant<Args...>& v)
    -> variant_cast_proxy<Args...> {
    return {v};
}

LoxObj FromLiteralValue(const Lexer::LiteralValue& value) {
    return LoxObj{variant_cast(value)};
}

bool IsTruthy(const LoxObj& obj) {
    return std::visit(overloaded{[](std::monostate /*m*/) { return false; },
                                 [](bool b) { return b; },
                                 [](auto&& arg) { return true; }},
                      obj);
}

} // namespace Loxpp::Object