#include <loxpp_pch.h>

#include <Error.h>
#include <Lox.h>

namespace Loxpp {

namespace Literals {
using namespace std::literals;
static constexpr auto Prompt{">> "sv};
} // namespace Literals

class Lox : public ILox {
  public:
    virtual void RunFile(std::string filePath) override {
        std::ifstream file{filePath};
        if (!file.is_open()) {
            throw Error::UsageException(
                Error::UsageException::Type::CanNotOpenFile);
        }
        std::stringstream buf;
        buf << file.rdbuf();
        Run(buf.str());
    }
    virtual void RunPrompt() override {

        std::string input;
        std::cout << Literals::Prompt;

        while (std::getline(std::cin, input)) {
            Run(input);
            std::cout << Literals::Prompt;
        }
    }

  private:
    void Run(std::string source) {}
};

ILox &GetLox() {
    static Lox s_instance{};
    return s_instance;
}
} // namespace Loxpp