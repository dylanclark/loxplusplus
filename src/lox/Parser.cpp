#include <loxpp_pch.h>

#include <Parser.h>

namespace Loxpp::Parser {

using namespace Expressions;
using namespace Lexer;

Parser::Parser(std::vector<TokenPtr>&& tokens) : m_tokens(std::move(tokens)) {}

ExprVariant Parser::Expression() { return Equality(); }

ExprVariant Parser::Equality() {
    ExprVariant expr{Comparison()};

    while (Match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
        const TokenPtr& op{Previous()};
        ExprVariant right{Comparison()};
        expr = MakeBinaryExpr(std::move(expr), std::make_unique<Token>(*op),
                              std::move(right));
    }

    return expr;
}

ExprVariant Parser::Comparison() { return Equality(); }

// Check to see if current token has any of the given types
// TODO: initializer list
bool Parser::Match(std::initializer_list<TokenType> types) {
    for (const auto& tokenType : types) {
        if (Check(tokenType)) {
            Advance();
            return true;
        }
    }
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