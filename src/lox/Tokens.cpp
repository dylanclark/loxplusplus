#include <loxpp_pch.h>

#include <Tokens.h>

namespace Loxpp::Lexer {
#pragma region Public methods

// Constructor
Token::Token(TokenType type, std::string lexeme,
             std::optional<LiteralValue> literal, int line)
    : m_type(type), m_lexeme(lexeme), m_literal(literal), m_line(line) {}

// Copy constructor
Token::Token(const Token& other)
    : m_type(other.GetType()), m_lexeme(other.GetLexeme()),
      m_literal(other.GetLiteral()), m_line(other.GetLine()) {}

#pragma endregion

#pragma region Helpers

std::string ToString(TokenType type) {
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

const std::unordered_map<std::string, TokenType>& GetReservedKeywords() {

    static const std::unordered_map<std::string, TokenType>
        s_reservedKeywordsMap{[]() {
            std::unordered_map<std::string, TokenType> map{};
            map.insert({"and", TokenType::AND});
            map.insert({"class", TokenType::CLASS});
            map.insert({"else", TokenType::ELSE});
            map.insert({"for", TokenType::FOR});
            map.insert({"fun", TokenType::FUN});
            map.insert({"if", TokenType::IF});
            map.insert({"nil", TokenType::NIL});
            map.insert({"or", TokenType::OR});
            map.insert({"print", TokenType::PRINT});
            map.insert({"return", TokenType::RETURN});
            map.insert({"super", TokenType::SUPER});
            map.insert({"this", TokenType::THIS});
            map.insert({"true", TokenType::TRUE});
            map.insert({"var", TokenType::VAR});
            map.insert({"while", TokenType::WHILE});
            return map;
        }()};

    return s_reservedKeywordsMap;
}

#pragma endregion

} // namespace Loxpp::Lexer
