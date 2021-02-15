#include <loxpp_pch.h>

#include <Error.h>
#include <Lox.h>
#include <Parser.h>
#include <Print.h>
#include <Scanner.h>
#include <Tokens.h>

namespace Loxpp {

namespace Literals {
using namespace std::literals;
static constexpr auto Prompt{">> "sv};
} // namespace Literals

using namespace Lexer;

class Lox : public ILox {
  public:
    virtual void RunFile(std::string filePath) override;
    virtual void RunPrompt() override;

  private:
    void Run(std::string source);
    void Error(int line, std::string message);

    bool m_hadError{false};
};

void Lox::RunFile(std::string filePath) {
    std::ifstream file{filePath};
    if (!file.is_open()) {
        throw Error::UsageException(
            Error::UsageException::Type::CanNotOpenFile);
    }
    std::stringstream buf;
    buf << file.rdbuf();
    Run(buf.str());
}

void Lox::RunPrompt() {

    std::string input;
    std::cout << Literals::Prompt;

    while (std::getline(std::cin, input)) {
        Run(input);
        m_hadError = false;
        std::cout << Literals::Prompt;
    }
}

void Lox::Run(std::string source) {
    Scanner scanner{source};
    try {
        std::vector<std::unique_ptr<Token>> tokens{scanner.ScanTokens()};

        Parser::Parser parser{std::move(tokens)};
        Parser::Expressions::ExprVariant expr{parser.Parse()};
        std::cout << expr << std::endl;
    } catch (const Error::SyntaxError& e) {
        m_hadError = true;
        std::cout << e.what() << std::endl;
    }
}

void Lox::Error(int /*line*/, std::string /*message*/) { m_hadError = true; }

ILox& GetLox() {
    static Lox s_instance{};
    return s_instance;
}
} // namespace Loxpp