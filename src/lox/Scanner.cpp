#include <loxpp_pch.h>

#include <Scanner.h>

namespace Loxpp::Lexer {

#pragma region Public methods

Scanner::Scanner(std::string source) : m_source(source) {}

const std::vector<Token>& Scanner::ScanTokens() {
    while (!IsAtEnd()) {
        // Beginning of next lexeme
        m_start = m_current;
        ScanToken();
    }

    m_tokens.push_back(Token(TokenType::END, "", "", m_line));
    return m_tokens;
}

#pragma endregion

#pragma region Private methods

bool Scanner::IsAtEnd() const { return m_current >= m_source.size(); }

void Scanner::ScanToken() {
    char c{Advance()};
    switch (c) {
    case '(':
        AddToken(TokenType::LEFT_PAREN);
        break;
    case ')':
        AddToken(TokenType::RIGHT_PAREN);
        break;
    case '{':
        AddToken(TokenType::LEFT_BRACE);
        break;
    case '}':
        AddToken(TokenType::RIGHT_BRACE);
        break;
    case ',':
        AddToken(TokenType::COMMA);
        break;
    case '.':
        AddToken(TokenType::DOT);
        break;
    case '-':
        AddToken(TokenType::MINUS);
        break;
    case '+':
        AddToken(TokenType::PLUS);
        break;
    case ';':
        AddToken(TokenType::SEMICOLON);
        break;
    case '*':
        AddToken(TokenType::STAR);
        break;
    }
}

char Scanner::Advance() {
    char c{m_source[m_current]};
    m_current++;

    return c;
}

void Scanner::AddToken(TokenType type, std::optional<std::string> literal) {
    std::string text{m_source.substr(m_start, m_current)};
    m_tokens.push_back(Token(type, text, literal, m_line));
}

#pragma endregion
} // namespace Loxpp::Lexer