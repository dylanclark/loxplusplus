#include <Expr.h>
#include <Tokens.h>

#include <iostream>

// explicit deduction guide (not needed as of C++20)
template <class... Ts> struct overloaded : Ts... {
    using Ts::operator()...;
};                                                             // (1)
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>; // (2)

// ExprVariant
std::ostream& operator<<(std::ostream& stream,
                         const Loxpp::Parser::Expressions::ExprVariant& expr);
// Token
std::ostream& operator<<(std::ostream& stream,
                         const Loxpp::Lexer::Token& token);
// Literal
std::ostream& operator<<(std::ostream& stream,
                         const Loxpp::Lexer::LiteralValue& value);
