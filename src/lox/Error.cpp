#include <loxpp_pch.h>

#include <Error.h>

namespace Loxpp::Error {
UsageException::UsageException(Type type)
    : m_type(type), m_message(buildMessage(type)) {}

const char *UsageException::what() const noexcept { return m_message.c_str(); }

/*static*/ std::string UsageException::buildMessage(Type type) {
    std::ostringstream stream;
    stream << "Usage error:\n\t" << m_whatStrings[static_cast<size_t>(type)]
           << std::endl;
    return stream.str();
}

} // namespace Loxpp::Error