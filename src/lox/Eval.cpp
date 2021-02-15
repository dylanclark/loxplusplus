#include <loxpp_pch.h>

#include <Eval.h>
#include <VisitHelpers.h>

namespace Loxpp::Expressions {

Evaluator::Evaluator() = default;

void Evaluator::Eval(const Expr& expr) {
    std::visit(
        overloaded{// Define << overload for each type of the variant here
                   [](const BinaryExprPtr& binaryExpr) {},
                   [](const GroupingExprPtr& groupingExpr) {},
                   [](const LiteralExprPtr& literalExpr) {},
                   [](const UnaryExprPtr& unaryExpr) {}},
        expr);
}
} // namespace Loxpp::Expressions