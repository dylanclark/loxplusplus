#include <loxpp_pch.h>

#include <Parser.h>

#include <cstdarg>

namespace Loxpp::Parser {

using namespace Expressions;
using namespace Lexer;

Parser::Parser(std::vector<TokenPtr>&& tokens) : m_tokens(std::move(tokens)) {}

ExprPtr Parser::Expression() { return Equality(); }

ExprPtr Parser::Equality() {
    ExprPtr expr{Comparison()};

    // while (Match(2, TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL)) {
    //     const TokenPtr& op{Previous()};
    //     ExprPtr right{Comparison()};
    //     expr = std::make_unique<BinaryExpr>(expr, op, right);
    // }

    return expr;
}

ExprPtr Parser::Comparison() { return nullptr; }

// Check to see if current token has any of the given types
bool Parser::Match(int ct, TokenType types...) {
    va_list(args);
    va_start(args, types);

    for (int i = 0; i < ct; i++) {
        TokenType type{va_arg(args, TokenType)};
        if (Check(type)) {
            Advance();
            return true;
        }
    }

    va_end(args);

    return false;
}

// Return true if current token has given type
bool Parser::Check(TokenType type) {
    if (IsAtEnd()) {
        return false;
    }

    return Peek()->GetType() == type;
}

bool Parser::IsAtEnd() const { return Peek()->GetType() == TokenType::END; }

const TokenPtr& Parser::Advance() {
    if (!IsAtEnd()) {
        m_current++;
    }

    return Previous();
}

const TokenPtr& Parser::Peek() const { return m_tokens.at(m_current); }

const TokenPtr& Parser::Previous() { return m_tokens.at(m_current - 1); }

} // namespace Loxpp::Parser