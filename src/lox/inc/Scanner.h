#pragma once

#include "Tokens.h"

#include <optional>
#include <string>
#include <vector>

namespace Loxpp::Lexer {

class Scanner {
  public:
    Scanner(std::string source);
    const std::vector<Token>& ScanTokens();

  private:
    bool IsAtEnd() const;
    void ScanToken();
    char Advance();
    void AddToken(TokenType type,
                  std::optional<std::string> literal = std::nullopt);

    std::string m_source;
    std::vector<Token> m_tokens;
    int m_start{0};
    int m_current{0};
    int m_line{1};
};

} // namespace Loxpp::Lexer