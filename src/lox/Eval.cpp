#include <loxpp_pch.h>

#include <Eval.h>
#include <VisitHelpers.h>

namespace Loxpp::Expressions {

using namespace Object;

Evaluator::Evaluator() = default;

LoxObj Evaluator::Eval(const Expr& expr) {
    return std::visit(
        overloaded{
            // Define Eval overload for each type of the variant here
            [this](const BinaryExprPtr& binaryExpr) {
                return Eval(binaryExpr);
            },
            [this](const GroupingExprPtr& groupingExpr) {
                return Eval(groupingExpr);
            },
            [this](const LiteralExprPtr& literalExpr) {
                return Eval(literalExpr);
            },
            [this](const UnaryExprPtr& unaryExpr) { return Eval(unaryExpr); }},
        expr);
}

LoxObj Evaluator::Eval(const BinaryExprPtr& expr) { return LoxObj{}; }
LoxObj Evaluator::Eval(const GroupingExprPtr& expr) { return LoxObj{}; }
LoxObj Evaluator::Eval(const LiteralExprPtr& expr) { return LoxObj{}; }
LoxObj Evaluator::Eval(const UnaryExprPtr& expr) { return LoxObj{}; }

} // namespace Loxpp::Expressions