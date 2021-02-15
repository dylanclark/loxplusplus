#pragma once

#include <Uncopyable.h>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>

namespace Loxpp::Lexer {

enum class TokenType {
    // Single-character tokens.
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,

    // One or two character tokens.
    BANG,
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,

    // Literals.
    IDENTIFIER,
    STRING,
    NUMBER,

    // Keywords.
    AND,
    CLASS,
    ELSE,
    FALSE,
    FUN,
    FOR,
    IF,
    NIL,
    OR,
    PRINT,
    RETURN,
    SUPER,
    THIS,
    TRUE,
    VAR,
    WHILE,

    END
};

// String util for TokenType
std::string ToString(TokenType type);

// Accessor for a map that will contain all reserved keywords and their token
// type
const std::unordered_map<std::string, TokenType>& GetReservedKeywords();

// Variant type is a union of our supported literals: string, double, bool, and
// null. Null is represented by std::monostate`
using LiteralValue = std::variant<std::monostate, std::string, double, bool>;

// A token represents a valid part of the Loxpp alphabet
// It has a type, a lexeme (i.e. the textual representation of the token in src
// code), and optionally a literal value We also keep track of line for use in
// error messages
class Token {
  public:
    Token(TokenType type, std::string lexeme,
          std::optional<LiteralValue> literal, int line);
    virtual ~Token() = default;
    // We impl copy constr
    Token(const Token&);
    // Delete other constrs
    auto operator=(const Token&) -> Token& = delete;
    Token(Token&&) = delete;
    auto operator=(Token&&) -> Token& = delete;

    TokenType GetType() const { return m_type; }
    const std::string& GetLexeme() const { return m_lexeme; }
    const std::optional<LiteralValue>& GetLiteral() const { return m_literal; }
    int GetLine() const { return m_line; }

  private:
    const TokenType m_type;
    const std::string m_lexeme;
    const std::optional<LiteralValue> m_literal;
    const int m_line;
};

// Shorthand for a unique_ptr to a token
using TokenPtr = std::unique_ptr<Lexer::Token>;

} // namespace Loxpp::Lexer