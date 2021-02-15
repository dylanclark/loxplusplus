#pragma once

#include <Error.h>
#include <Tokens.h>

#include <array>
#include <exception>
#include <sstream>
#include <string>

// Errors specific to lox-core library
namespace Loxpp::Error {

// Represents a syntax error described by `message` in `where` of line `line`
class SyntaxError : public std::exception {
  public:
    SyntaxError(int line, const std::string& where, const std::string& message);

    virtual const char* what() const noexcept override;

  private:
    static std::string BuildMessage(int line, const std::string& where,
                                    const std::string& message);
    std::string m_message;
};

class RuntimeError : public std::exception {

  public:
    RuntimeError(const Lexer::TokenPtr& token, const std::string& message);

    virtual const char* what() const noexcept override;

  private:
    std::string m_message;
    Lexer::Token m_token;
};

} // namespace Loxpp::Error