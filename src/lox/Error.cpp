#include <loxpp_pch.h>

#include <_Error.h>

namespace Loxpp::Error {

#pragma region Usage Exception

UsageException::UsageException(Type type)
    : m_type(type), m_message(BuildMessage(type)) {}

const char* UsageException::what() const noexcept { return m_message.c_str(); }

/*static*/ std::string UsageException::BuildMessage(Type type) {
    std::ostringstream stream;
    stream << "Usage error:\n\t" << m_whatStrings[static_cast<size_t>(type)]
           << std::endl;
    return stream.str();
}

#pragma endregion

#pragma region Syntax Error

SyntaxError::SyntaxError(int line, const std::string& where,
                         const std::string& message)
    : m_message(BuildMessage(line, where, message)) {}

const char* SyntaxError::what() const noexcept { return m_message.c_str(); }

/*static*/ std::string SyntaxError::BuildMessage(int line,
                                                 const std::string& where,
                                                 const std::string& message) {
    std::ostringstream stream;
    stream << "[line " << line << "] Error " << where << ": " << message;
    return stream.str();
}

#pragma endregion

#pragma region Runtime Error
RuntimeError::RuntimeError(const Lexer::TokenPtr& token,
                           const std::string& message)
    : m_token(*token), m_message(message) {}

const char* RuntimeError::what() const noexcept { return m_message.c_str(); }

} // namespace Loxpp::Error