#pragma once

#include "Expr.h"
#include "Tokens.h"

#include <memory>
#include <vector>

namespace Loxpp::Parser {

// Parser is a class responsible for turning sequential tokens into an
// expression tree (AST)
class Parser {
  public:
    Parser(std::vector<Lexer::TokenPtr>&& tokens);
    Expressions::Expr Parse();

  private:
    Expressions::Expr Expression();
    Expressions::Expr Equality();
    Expressions::Expr Comparison();
    Expressions::Expr Term();
    Expressions::Expr Factor();
    Expressions::Expr Unary();
    Expressions::Expr Primary();

    bool Match(std::initializer_list<Lexer::TokenType> types);
    bool Check(Lexer::TokenType type);
    bool IsAtEnd() const;

    const Lexer::TokenPtr& Advance();
    const Lexer::TokenPtr& Peek() const;
    const Lexer::TokenPtr& Previous();
    const Lexer::TokenPtr& Consume(Lexer::TokenType type, std::string message);

    Error::SyntaxError Error(const Lexer::TokenPtr& token, std::string message);
    void Synchronize();

    std::vector<Lexer::TokenPtr> m_tokens;
    int m_current{0};
};

} // namespace Loxpp::Parser