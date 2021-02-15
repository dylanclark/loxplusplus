#pragma once

#include <Expr.h>

namespace Loxpp::Expressions {

class Evaluator {
  public:
    Evaluator();

    void Eval(const Expr& expr);
};

} // namespace Loxpp::Expressions