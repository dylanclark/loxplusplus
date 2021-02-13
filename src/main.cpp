#include <loxpp_pch.h>

#include <Lox.h>

using namespace Loxpp;

int main(int argc, char **argv) noexcept {
    try {
        if (argc > 2) {
            std::cout << "Usage: jlox [script]" << std::endl;
            return -1;
        } else if (argc == 2) {
            GetLox().RunFile(argv[1]);
        } else {
            GetLox().RunPrompt();
        }
        return 0;
    } catch (const std::exception &e) {
        std::cout << e.what();
    }
}