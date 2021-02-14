#pragma once

#include "Tokens.h"
#include <Uncopyable.h>

#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace Loxpp::Lexer {

class Scanner : public Uncopyable {
  public:
    Scanner(std::string source);

    const std::vector<std::unique_ptr<Token>>& ScanTokens();

  private:
    void ScanToken();
    char Advance();
    char Peek() const;
    char PeekNext() const;

    bool TryMatch(char expected);
    bool IsAtEnd() const;
    bool IsDigit(char c);
    bool IsAlpha(char c);
    bool IsAlphaNumeric(char c);

    std::string GetCurrentText();

    void AddToken(TokenType type,
                  std::optional<LiteralValue> literal = std::nullopt);
    void AddStringToken();
    void AddNumber();
    void AddIdentifier();

    std::string m_source;
    std::vector<std::unique_ptr<Token>> m_tokens;
    int m_start{0};
    int m_current{0};
    int m_line{1};
};

} // namespace Loxpp::Lexer