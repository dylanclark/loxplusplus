#pragma once

#include <string>
#include <variant>

namespace Loxpp::Object {

// LoxObj: Type returned by evaluating an expression
using LoxObj = std::variant<std::monostate, std::string, double, bool>;

} // namespace Loxpp::Object