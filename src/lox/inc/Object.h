#pragma once

#include <Tokens.h>

#include <string>
#include <variant>

namespace Loxpp::Object {

// LoxObj: Type returned by evaluating an expression
using LoxObj = std::variant<std::monostate, std::string, double, bool>;

LoxObj FromLiteralValue(const Lexer::LiteralValue& value);
bool IsTruthy(const LoxObj& obj);
} // namespace Loxpp::Object