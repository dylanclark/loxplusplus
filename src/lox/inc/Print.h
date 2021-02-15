#include <Expr.h>
#include <Tokens.h>

#include <iostream>

// This file contains declarations of the `<<` overloads for various types we'd
// like to pretty-print when debugging

// explicit deduction guide - useful for helping implement pattern-matching like
// pattern with variant types
template <class... Ts> struct overloaded : Ts... {
    using Ts::operator()...;
};                                                             // (1)
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>; // (2)

// << ExprVariant
std::ostream& operator<<(std::ostream& stream,
                         const Loxpp::Parser::Expressions::ExprVariant& expr);
// << Token
std::ostream& operator<<(std::ostream& stream,
                         const Loxpp::Lexer::Token& token);
// << LiteralValue
std::ostream& operator<<(std::ostream& stream,
                         const Loxpp::Lexer::LiteralValue& value);
