#include <Tokens.h>
#include <loxpp_pch.h>

namespace Loxpp::Lexer {

namespace Literals {
constexpr auto Space{" "};
constexpr auto TokenName{"Token"};
constexpr auto Colon{":"};
constexpr auto OpenBracket{"{"};
constexpr auto CloseBracket{"}"};
constexpr auto Type{"Type"};
constexpr auto Lex{"Lex"};
constexpr auto Literal{"Literal"};
} // namespace Literals
#pragma region Public methods

Token::Token(TokenType type, std::string lexeme,
             std::optional<LiteralValue> literal, int line)
    : m_type(type), m_lexeme(lexeme), m_literal(literal), m_line(line) {}

// impl << instead
std::string Token::ToString() const {
    using namespace Literals;
    std::ostringstream stream;
    stream << TokenName << Space << OpenBracket << Space << Type << Colon
           << Space << ToString(m_type) << Space << Lex << Colon << Space
           << m_lexeme << Space;
    if (m_literal.has_value()) {
        stream << Literal << Colon << Space;
        std::visit([&stream](const auto& variant) { stream << variant; },
                   *m_literal);
        stream << Space;
    }
    stream << CloseBracket << std::endl;
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
