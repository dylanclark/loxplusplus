#include <Tokens.h>
#include <loxpp_pch.h>

namespace Loxpp::Lexer {

#pragma region Public methods

Token::Token(TokenType type, std::string lexeme,
             std::optional<std::string> literal, int line)
    : m_type(type), m_lexeme(lexeme), m_literal(literal), m_line(line) {}

std::string Token::ToString() const {
    std::ostringstream stream;
    const std::string literalStr{m_literal.has_value() ? *m_literal : "[null]"};
    stream << ToString(m_type) << " " << m_lexeme << " " << literalStr;
    return stream.str();
}

#pragma endregion

#pragma region Private methods

std::string Token::ToString(TokenType type) {
    using namespace std::literals;
    static constexpr std::array<std::string_view, 39> strings{
        {// Single-character tokens.
         {"LEFT_PAREN"sv},
         {"RIGHT_PAREN"sv},
         {"LEFT_BRACE"sv},
         {"RIGHT_BRACE"sv},
         {"COMMA"sv},
         {"DOT"sv},
         {"MINUS"sv},
         {"PLUS"sv},
         {"SEMICOLON"sv},
         {"SLASH"sv},
         {"STAR"sv},
         {"BANG"sv},
         {"BANG_EQUAL"sv},
         {"EQUAL"sv},
         {"EQUAL_EQUAL"sv},
         {"GREATER"sv},
         {"GREATER_EQUAL"sv},
         {"LESS"sv},
         {"LESS_EQUAL"sv},
         {"IDENTIFIER"sv},
         {"STRING"sv},
         {"NUMBER"sv},
         {"AND"sv},
         {"CLASS"sv},
         {"ELSE"sv},
         {"FALSE"sv},
         {"FUN"sv},
         {"FOR"sv},
         {"IF"sv},
         {"NIL"sv},
         {"OR"sv},
         {"PRINT"sv},
         {"RETURN"sv},
         {"SUPER"sv},
         {"THIS"sv},
         {"TRUE"sv},
         {"VAR"sv},
         {"WHILE"sv},
         {"END"sv}}};
    return std::string{strings[static_cast<size_t>(type)]};
}

#pragma endregion

} // namespace Loxpp::Lexer
