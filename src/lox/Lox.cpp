#include <loxpp_pch.h>

#include <Interpreter.h>
#include <Lox.h>
#include <Parser.h>
#include <Print.h>
#include <Scanner.h>
#include <Stmt.h>
#include <Tokens.h>
#include <_Error.h>

namespace Loxpp {

namespace Literals {
using namespace std::literals;
static constexpr auto Prompt{">> "sv};
} // namespace Literals

using namespace Lexer;

// Implementation of the ILox interface for the lox-core library
// This is the main entry point to the application - we start by either running
// a file or running a REPL `Run` consists of scanning the source coe into
// tokens, parsing the tokens into an expression tree, and [TODO: right now we
// just print them]
class Lox : public ILox {
  public:
    virtual void RunFile(std::string filePath) override;
    virtual void RunPrompt() override;

  private:
    void Run(std::string&& source);
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
    Run(std::move(buf.str()));
}

void Lox::RunPrompt() {

    std::string input;
    std::cout << Literals::Prompt;

    while (std::getline(std::cin, input)) {
        Run(std::move(input));
        m_hadError = false;
        std::cout << Literals::Prompt;
    }
}

void Lox::Run(std::string&& source) {
    Scanner scanner{std::move(source)};
    try {
        std::vector<std::unique_ptr<Token>> tokens{scanner.ScanTokens()};
        Parser::Parser parser{std::move(tokens)};
        std::vector<Statements::Stmt> statements{parser.Parse()};

        //        Expressions::Interpreter interpreter{};
        //        interpreter.Evaluate(expr);

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