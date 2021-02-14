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

const std::unordered_map<std::string, TokenType>& GetReservedKeywords();
std::string ToString(TokenType type);

using LiteralValue = std::variant<std::string, double>;

class Token : public Uncopyable {
  public:
    Token(TokenType type, std::string lexeme,
          std::optional<LiteralValue> literal, int line);

    TokenType GetType() const { return m_type; }
    const std::string& GetLexeme() const { return m_lexeme; }
    const std::optional<LiteralValue>& GetLiteral() const { return m_literal; }
    int GetLine() const { return m_line; }

    friend std::ostream& operator<<(std::ostream& os, const Token& token);

  private:
    const TokenType m_type;
    const std::string m_lexeme;
    const std::optional<LiteralValue> m_literal;
    const int m_line;
};

using TokenPtr = std::unique_ptr<Lexer::Token>;

} // namespace Loxpp::Lexer