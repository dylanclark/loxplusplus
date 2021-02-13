#include <loxpp_pch.h>

#include <err.h>

using namespace Loxpp;

// FD
void runFile(std::string filePath);
void runPrompt();

int main(int argc, char **argv) noexcept {
  try {
    if (argc > 2) {
      std::cout << "Usage: jlox [script]" << std::endl;
      return -1;
    } else if (argc == 2) {
      runFile(argv[1]);
    } else {
      runPrompt();
    }
    return 0;
  } catch (const std::exception &e) {
    std::cout << e.what();
  }
}

void runFile(std::string filePath) {
  std::ifstream file{filePath};
  if (!file.is_open()) {
    throw Err::UsageException(Err::UsageException::Type::CanNotOpenFile);
  }
}

void runPrompt() {
  std::string input;

  std::cout << "> ";

  while (std::getline(std::cin, input)) {
    std::cout << input << std::endl;
    std::cout << "> ";
  }
}