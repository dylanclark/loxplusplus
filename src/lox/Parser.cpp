#include <loxpp_pch.h>

#include <Parser.h>
#include <_Error.h>

namespace Loxpp::Parser {

using namespace Expressions;
using namespace Lexer;
using namespace Statements;

/*

Parser implementation: Reponsible for parsing a flat list of tokens into an
expression tree conforming to the languages grammar. Grammar is described here
in BNF:

expression     → equality ;
equality       → comparison ( ( "!=" | "==" ) comparison )* ;
comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
term           → factor ( ( "-" | "+" ) factor )* ;
factor         → unary ( ( "/" | "*" ) unary )* ;
unary          → ( "!" | "-" ) unary
               | primary ;
primary        → NUMBER | STRING | "true" | "false" | "nil"
               | "(" expression ")" ;
*/
Parser::Parser(std::vector<TokenPtr>&& tokens) : m_tokens(std::move(tokens)) {}

std::vector<Stmt> Parser::Parse() {
    std::vector<Stmt> statements;
    return statements;
    //    try {
    //        return Expression();
    //    } catch (const Error::SyntaxError& e) {
    //        return MakeLiteralExpr(std::monostate());
    //    }
}

// expression -> equality
Expr Parser::Expression() { return Equality(); }

// equality -> comparison ( ( "!=" | "== ") comparison)*
Expr Parser::Equality() {
    Expr expr{Comparison()};

    while (Match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
        const TokenPtr& op{Previous()};
        Expr right{Comparison()};
        expr = MakeBinaryExpr(std::move(expr), std::make_unique<Token>(*op),
                              std::move(right));
    }

    return expr;
}

// comparison -> term ( ( ">" | ">=" | "<" | "<=" ) term )*
Expr Parser::Comparison() {
    Expr expr{Term()};

    while (Match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS,
                  TokenType::LESS_EQUAL})) {
        const TokenPtr& op{Previous()};
        Expr right{Term()};
        expr = MakeBinaryExpr(std::move(expr), std::make_unique<Token>(*op),
                              std::move(right));
    }

    return expr;
}

// term           → factor ( ( "-" | "+" ) factor )* ;
Expr Parser::Term() {
    Expr expr{Factor()};

    while (Match({TokenType::MINUS, TokenType::PLUS})) {
        const TokenPtr& op{Previous()};
        Expr right{Factor()};
        expr = MakeBinaryExpr(std::move(expr), std::make_unique<Token>(*op),
                              std::move(right));
    }

    return expr;
}

// factor         → unary ( ( "/" | "*" ) unary )* ;
Expr Parser::Factor() {
    Expr expr{Unary()};

    while (Match({TokenType::SLASH, TokenType::STAR})) {
        const TokenPtr& op{Previous()};
        Expr right{Unary()};
        expr = MakeBinaryExpr(std::move(expr), std::make_unique<Token>(*op),
                              std::move(right));
    }

    return expr;
}

// unary          → ( "!" | "-" ) unary | primary
Expr Parser::Unary() {
    if (Match({TokenType::BANG, TokenType::MINUS})) {
        const TokenPtr& op{Previous()};
        Expr right{Unary()};
        return MakeUnaryExpr(std::make_unique<Token>(*op), std::move(right));
    }
    return Primary();
}

// primary    → NUMBER | STRING | "true" | "false" | "nil" | "(" expression")" ;
Expr Parser::Primary() {
    if (Match({TokenType::FALSE})) {
        return MakeLiteralExpr(false);
    }
    if (Match({TokenType::TRUE})) {
        return MakeLiteralExpr(true);
    }
    if (Match({TokenType::NIL})) {
        return MakeLiteralExpr(std::monostate());
    }
    if (Match({TokenType::NUMBER, TokenType::STRING})) {
        auto val{Previous()->GetLiteral().value()};
        return MakeLiteralExpr(std::move(val));
    }
    if (Match({TokenType::LEFT_PAREN})) {
        Expr expr{Expression()};
        Consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return MakeGroupingExpr(std::move(expr));
    }

    throw Error(Peek(), "Expect expression.");
}

// Check to see if current token has any of the given types
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

// If next token is of type `type`, consume it and advance
// Otherwise throw an error
const TokenPtr& Parser::Consume(TokenType type, std::string message) {
    if (Check(type)) {
        return Advance();
    }

    throw Error(Peek(), message);
}

Error::SyntaxError Parser::Error(const Lexer::TokenPtr& token,
                                 std::string message) {

    if (token->GetType() == TokenType::END) {
        return Error::SyntaxError(token->GetLine(), "at end", message);
    } else {
        std::string location{"at '" + token->GetLexeme() + "'"};
        return Error::SyntaxError(token->GetLine(), location, message);
    }
}

// After error, discard tokens until at beginning of next statement
void Parser::Synchronize() {
    Advance();
    while (!IsAtEnd()) {
        if (Previous()->GetType() == TokenType::SEMICOLON) {
            return;
        }

        switch (Peek()->GetType()) {
        case TokenType::CLASS:
        case TokenType::FUN:
        case TokenType::VAR:
        case TokenType::FOR:
        case TokenType::IF:
        case TokenType::WHILE:
        case TokenType::PRINT:
        case TokenType::RETURN:
            return;
        }

        Advance();
    }
}
} // namespace Loxpp::Parser