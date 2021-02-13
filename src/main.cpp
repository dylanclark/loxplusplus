#include <loxpp_pch.h>

// FD
void runFile(std::string filePath);
void runPrompt();

int main(int argc, char **argv) {
  if (argc > 2) {
    std::cout << "Usage: jlox [script]" << std::endl;
    return -1;
  } else if (argc == 2) {
    runFile(std::string(argv[argc]));
  } else {
    runPrompt();
  }
}

void runFile(std::string filePath) {
  std::ifstream file{filePath};
  if (!file.is_open()) {
    std::cout << "poo";
  }
}

void runPrompt() {}