#pragma once

#include <array>
#include <exception>
#include <sstream>
#include <string>

namespace Loxpp::Error {

// Represents a user exception - i.e. trying to run a file that doesn't exist
class UsageException : public std::exception {
  public:
    enum class Type {
        CanNotOpenFile,

        // Dont add after this
        _Max
    };

    UsageException(Type type);

    virtual const char* what() const noexcept override;

  private:
    static std::string BuildMessage(Type);

    static constexpr std::array<const char*, static_cast<size_t>(Type::_Max)>
        m_whatStrings{{"Can not open file specificed"}};

    const Type m_type;
    std::string m_message;
};

} // namespace Loxpp::Error