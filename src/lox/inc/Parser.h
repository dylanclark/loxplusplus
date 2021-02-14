#pragma once

#include "Expr.h"
#include "Tokens.h"

#include <memory>
#include <vector>

namespace Loxpp::Parser {

class Parser {
  public:
    Parser(std::vector<Lexer::TokenPtr>&& tokens);

  private:
    Expressions::ExprVariant Expression();
    Expressions::ExprVariant Equality();
    Expressions::ExprVariant Comparison();

    bool Match(std::initializer_list<Lexer::TokenType> types);
    bool Check(Lexer::TokenType type);
    bool IsAtEnd() const;

    const Lexer::TokenPtr& Advance();
    const Lexer::TokenPtr& Peek() const;
    const Lexer::TokenPtr& Previous();

    std::vector<Lexer::TokenPtr> m_tokens;
    int m_current{0};
};

} // namespace Loxpp::Parser