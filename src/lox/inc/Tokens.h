#pragma once

#include <iostream>
#include <optional>
#include <string>
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

using LiteralValue = std::variant<std::string, double>;

class Token {
  public:
    Token(TokenType type, std::string lexeme,
          std::optional<LiteralValue> literal, int line);

    ~Token() = default;
    Token(const Token&) = delete;
    Token& operator=(const Token&) = delete;
    Token(Token&& other) = delete;
    Token& operator=(Token&& other) = delete;

    std::string ToString() const;

  private:
    static std::string ToString(TokenType type);
    const TokenType m_type;
    const std::string m_lexeme;
    const std::optional<LiteralValue> m_literal;
    const int m_line;
};

} // namespace Loxpp::Lexer