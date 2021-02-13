#include <loxpp_pch.h>

#include <Error.h>
#include <Lox.h>

namespace Loxpp {

namespace Literals {
using namespace std::literals;
static constexpr auto Prompt{">> "sv};
} // namespace Literals

class Lox : public ILox {
    virtual void RunFile(std::string filePath) override {
        std::ifstream file{filePath};
        if (!file.is_open()) {
            throw Error::UsageException(
                Error::UsageException::Type::CanNotOpenFile);
        }
    }
    virtual void RunPrompt() override {

        std::string input;
        std::cout << Literals::Prompt;

        while (std::getline(std::cin, input)) {
            std::cout << input << std::endl;
            std::cout << Literals::Prompt;
        }
    }
};

ILox &GetLox() {
    static Lox s_instance{};
    return s_instance;
}
} // namespace Loxpp