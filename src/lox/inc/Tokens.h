#pragma once

#include <optional>
#include <string>

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

class Token {
  public:
    Token(TokenType type, std::string lexeme,
          std::optional<std::string> literal, int line);

    std::string ToString() const;

  private:
    static std::string ToString(TokenType type);
    const TokenType m_type;
    const std::string m_lexeme;
    const std::optional<std::string> m_literal;
    const int m_line;
};

} // namespace Loxpp::Lexer