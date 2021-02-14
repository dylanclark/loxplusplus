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
    Expressions::ExprPtr Expression();
    Expressions::ExprPtr Equality();
    Expressions::ExprPtr Comparison();

    bool Match(int ct, Lexer::TokenType types...);
    bool Check(Lexer::TokenType type);
    bool IsAtEnd() const;

    const Lexer::TokenPtr& Advance();
    const Lexer::TokenPtr& Peek() const;
    const Lexer::TokenPtr& Previous();

    std::vector<Lexer::TokenPtr> m_tokens;
    int m_current{0};
};

} // namespace Loxpp::Parser