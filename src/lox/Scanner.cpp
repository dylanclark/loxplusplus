#include <loxpp_pch.h>

#include <Error.h>
#include <Scanner.h>

#include <cctype>

namespace Loxpp::Lexer {

#pragma region Public methods

Scanner::Scanner(std::string source) : m_source(source) {}

const std::vector<std::unique_ptr<Token>>& Scanner::ScanTokens() {
    while (!IsAtEnd()) {
        // Beginning of next lexeme
        m_start = m_current;
        ScanToken();
    }

    m_tokens.push_back(
        std::make_unique<Token>(TokenType::END, "", std::nullopt, m_line));
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
    case '!':
        AddToken(TryMatch('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
        break;
    case '=':
        AddToken(TryMatch('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
        break;
    case '<':
        AddToken(TryMatch('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
        break;
    case '>':
        AddToken(TryMatch('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        break;
    case '/':
        if (TryMatch('/')) {
            // Comment goes to EOL, skip them
            while (Peek() != '\n' && !IsAtEnd()) {
                Advance();
            }
        } else {
            AddToken(TokenType::SLASH);
        }
        break;
    case '"':
        AddStringToken();
        break;
    case ' ':
    case '\r':
    case '\t':
        // Ignore whitespace
        break;
    case '\n':
        m_line++;
        break;
    default:
        if (IsDigit(c)) {
            AddNumber();
        } else {
            throw Error::SyntaxError(m_line, "", "Unexpected character.");
        }
    }
}

char Scanner::Advance() {
    char c{m_source[m_current]};
    m_current++;

    return c;
}

void Scanner::AddToken(TokenType type, std::optional<LiteralValue> literal) {
    const int len{m_current - m_start};
    std::string text{m_source.substr(m_start, len)};
    m_tokens.push_back(std::make_unique<Token>(type, text, literal, m_line));
}

bool Scanner::TryMatch(char expected) {
    // EOL
    if (IsAtEnd()) {
        return false;
    }

    // No Match
    if (m_source[static_cast<size_t>(m_current)] != expected) {
        return false;
    }

    // Consume next char, it matched!
    m_current++;
    return true;
}

char Scanner::Peek() const {
    if (IsAtEnd()) {
        return '\0';
    }
    return m_source[m_current];
}

char Scanner::PeekNext() const {
    if (m_current + 1 >= m_source.length()) {
        return '\0';
    }
    return m_source[m_current + 1];
}

void Scanner::AddStringToken() {
    while (Peek() != '"' && !IsAtEnd()) {
        if (Peek() == '\n') {
            m_line++;
        }
        Advance();
    }
    if (IsAtEnd()) {
        throw Error::SyntaxError(m_line, "", "Unterminated string.");
    }

    // The closing "
    Advance();

    const int startIndex{m_start + 1};
    const int endIndex{m_current - 1};
    const int len{endIndex - startIndex};

    std::string stringValue{m_source.substr(startIndex, len)};

    AddToken(TokenType::STRING, LiteralValue(stringValue));
}

bool Scanner::IsDigit(char c) {
    return std::isdigit(static_cast<unsigned char>(c));
}

void Scanner::AddNumber() {
    while (IsDigit(Peek())) {
        Advance();
    }

    if (Peek() == '.' && IsDigit(PeekNext())) {
        // Consume the '.'
        Advance();

        while (IsDigit(Peek())) {
            Advance();
        }
    }

    const auto strLen(m_current - m_start);
    const auto digitStr{m_source.substr(m_start, strLen)};
    const double value{std::stod(digitStr)};

    AddToken(TokenType::NUMBER, LiteralValue(value));
}

#pragma endregion
} // namespace Loxpp::Lexer