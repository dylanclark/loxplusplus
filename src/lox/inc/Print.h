#include <Expr.h>
#include <Tokens.h>

#include <iostream>

// This file contains declarations of the `<<` overloads for various types we'd
// like to pretty-print when debugging

// << Expr
std::ostream& operator<<(std::ostream& stream,
                         const Loxpp::Expressions::Expr& expr);
// << Token
std::ostream& operator<<(std::ostream& stream,
                         const Loxpp::Lexer::Token& token);
// << LiteralValue
std::ostream& operator<<(std::ostream& stream,
                         const Loxpp::Lexer::LiteralValue& value);
