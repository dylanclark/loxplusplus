#pragma once

#include <string>
#include <vector>

namespace Loxpp {

struct ILox {
    virtual void RunFile(std::string filePath) = 0;
    virtual void RunPrompt() = 0;
};

ILox& GetLox();

} // namespace Loxpp