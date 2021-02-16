#include <loxpp_pch.h>

#include <Interpreter.h>
#include <Print.h>
#include <VisitHelpers.h>
#include <_Error.h>

namespace Loxpp::Interpreter {

using namespace Expressions;
using namespace Object;
using namespace Lexer;
using namespace Statements;

Interpreter::Interpreter() = default;

void Interpreter::Interpret(const std::vector<Stmt>& statements) {
    try {
        for (const auto& stmt : statements) {
            Execute(stmt);
        }
        //    LoxObj result{Eval(expr)};
        //   std::cout << "\nResult:\n" << result << std::endl;
    } catch (const Error::RuntimeError& e) {
        // todo: error reporter
        std::cout << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "FATAL ERROR! TERMINATING: " << e.what();
        throw e;
    }
}

void Interpreter::Execute(const Stmt& stmt) {
    return std::visit(overloaded{[this](const PrintStmtPtr& printStmt) {

                                 },
                                 [this](const ExpressionStmtPtr& exprStmt) {

                                 }},
                      stmt);
}

LoxObj Interpreter::Eval(const Expr& expr) {
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

LoxObj Interpreter::Eval(const BinaryExprPtr& expr) {
    LoxObj leftObj{Eval(expr->left)};
    LoxObj rightObj{Eval(expr->right)};

    switch (expr->op->GetType()) {
    case (TokenType::MINUS): {
        return PerformArithmeticOperation(expr->op, leftObj, rightObj,
                                          std::minus());
    }
    case (TokenType::SLASH): {
        return PerformArithmeticOperation(expr->op, leftObj, rightObj,
                                          std::divides());
    }
    case (TokenType::STAR): {
        return PerformArithmeticOperation(expr->op, leftObj, rightObj,
                                          std::multiplies());
    }
    case (TokenType::GREATER): {
        return PerformLogicalOperation(expr->op, leftObj, rightObj,
                                       std::greater());
    }
    case (TokenType::GREATER_EQUAL): {
        return PerformLogicalOperation(expr->op, leftObj, rightObj,
                                       std::greater_equal());
    }
    case (TokenType::LESS): {
        return PerformLogicalOperation(expr->op, leftObj, rightObj,
                                       std::less());
    }
    case (TokenType::LESS_EQUAL): {
        return PerformLogicalOperation(expr->op, leftObj, rightObj,
                                       std::less_equal());
    }
    case (TokenType::BANG_EQUAL): {
        return !IsEqual(leftObj, rightObj);
    }
    case (TokenType::EQUAL_EQUAL): {
        return IsEqual(leftObj, rightObj);
    }
    case (TokenType::PLUS): {
        // Addition
        if (std::holds_alternative<double>(leftObj) &&
            std::holds_alternative<double>(rightObj)) {
            const auto [left, right]{
                CheckNumberOperands(expr->op, leftObj, rightObj)};
            return left + right;
        }
        // String concat
        if (std::holds_alternative<std::string>(leftObj) &&
            std::holds_alternative<std::string>(rightObj)) {
            const std::string& leftStr{std::get<std::string>(leftObj)};
            const std::string& rightStr{std::get<std::string>(rightObj)};
            return leftStr + rightStr;
        }

        throw Error::RuntimeError(
            expr->op, "Operands must be two numbers or two strings.");
    }
    }
    // Should be unreachable
    throw Error::RuntimeError(expr->op, "Unexpected operator.");
}

LoxObj Interpreter::Eval(const GroupingExprPtr& expr) {
    return Eval(expr->expression);
}

LoxObj Interpreter::Eval(const LiteralExprPtr& expr) {
    return FromLiteralValue(expr->value);
}

LoxObj Interpreter::Eval(const UnaryExprPtr& expr) {
    LoxObj right{Eval(expr->right)};

    switch (expr->op->GetType()) {
    case (TokenType::MINUS): {
        double number{CheckNumberOperand(expr->op, right)};
        return (-number);
    }
    case (TokenType::BANG): {
        return !IsTruthy(right);
    }
    }

    return LoxObj{};
}

bool Interpreter::IsEqual(const Object::LoxObj& objLeft,
                          const Object::LoxObj& objRight) {
    return objLeft == objRight;
}

double Interpreter::PerformArithmeticOperation(
    const Lexer::TokenPtr& op, const Object::LoxObj& objLeft,
    const Object::LoxObj& objRight,
    std::function<double(double, double)> func) {
    const auto [left, right]{CheckNumberOperands(op, objLeft, objRight)};
    return func(left, right);
}

bool Interpreter::PerformLogicalOperation(
    const Lexer::TokenPtr& op, const Object::LoxObj& objLeft,
    const Object::LoxObj& objRight, std::function<bool(double, double)> func) {
    const auto [left, right]{CheckNumberOperands(op, objLeft, objRight)};
    return func(left, right);
}

double Interpreter::CheckNumberOperand(const TokenPtr& op, const LoxObj& obj) {
    const double* d{std::get_if<double>(&obj)};
    if (d == nullptr) {
        throw Error::RuntimeError(op, "Operand must be a number.");
    }
    return *d;
}

std::pair<double, double>
Interpreter::CheckNumberOperands(const Lexer::TokenPtr& op,
                                 const Object::LoxObj& objLeft,
                                 const Object::LoxObj& objRight) {
    const double* left{std::get_if<double>(&objLeft)};
    const double* right{std::get_if<double>(&objRight)};

    if (left == nullptr || right == nullptr) {
        throw Error::RuntimeError(op, "Operands must be two numbers");
    }
    return std::make_pair(*left, *right);
}

} // namespace Loxpp::Interpreter