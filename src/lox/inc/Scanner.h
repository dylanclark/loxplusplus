#pragma once

#include "Tokens.h"

#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace Loxpp::Lexer {

class Scanner {
  public:
    Scanner(std::string source);

    ~Scanner() = default;
    Scanner(const Scanner&) = delete;
    Scanner& operator=(const Scanner&) = delete;
    Scanner(Scanner&& other) = delete;
    Scanner& operator=(Scanner&& other) = delete;

    const std::vector<std::unique_ptr<Token>>& ScanTokens();

  private:
    bool IsAtEnd() const;
    void ScanToken();
    char Advance();
    void AddToken(TokenType type,
                  std::optional<LiteralValue> literal = std::nullopt);
    bool TryMatch(char expected);
    char Peek() const;
    char PeekNext() const;
    void AddStringToken();
    bool IsDigit(char c);
    void AddNumber();

    std::string m_source;
    std::vector<std::unique_ptr<Token>> m_tokens;
    int m_start{0};
    int m_current{0};
    int m_line{1};
};

} // namespace Loxpp::Lexer