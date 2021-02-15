#include <loxpp_pch.h>

#include <Eval.h>
#include <VisitHelpers.h>

namespace Loxpp::Expressions {

using namespace Object;
using namespace Lexer;

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

LoxObj Evaluator::Eval(const GroupingExprPtr& expr) {
    return Eval(expr->expression);
}

LoxObj Evaluator::Eval(const LiteralExprPtr& expr) {
    return FromLiteralValue(expr->value);
}

LoxObj Evaluator::Eval(const UnaryExprPtr& expr) {
    LoxObj right{Eval(expr->right)};

    switch (expr->op->GetType()) {
    case (TokenType::MINUS): {
        double number{GetNumberElseThrow(expr->op, right)};
        return (-number);
    }
    case (TokenType::BANG): {
        return !IsTruthy(right);
    }
    }

    return LoxObj{};
}

double Evaluator::GetNumberElseThrow(const TokenPtr& op, const LoxObj& obj) {
    const double* d{std::get_if<double>(&obj)};
    if (d == nullptr) {
        // throw new RuntimeException(type)
        return 0.;
    }
    return *d;
}
} // namespace Loxpp::Expressions