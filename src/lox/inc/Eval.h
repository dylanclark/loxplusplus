#pragma once

#include <Expr.h>
#include <Object.h>

namespace Loxpp::Expressions {

class Evaluator {
  public:
    Evaluator();

    Object::LoxObj Eval(const Expr& expr);

  private:
    Object::LoxObj Eval(const BinaryExprPtr& expr);
    Object::LoxObj Eval(const GroupingExprPtr& expr);
    Object::LoxObj Eval(const LiteralExprPtr& expr);
    Object::LoxObj Eval(const UnaryExprPtr& expr);
};

} // namespace Loxpp::Expressions