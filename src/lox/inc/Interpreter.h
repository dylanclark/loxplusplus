#pragma once

#include <Expr.h>
#include <Object.h>
#include <Stmt.h>
#include <Tokens.h>

#include <functional>
#include <utility>
#include <vector>

namespace Loxpp::Interpreter {

class Interpreter {
  public:
    Interpreter();

    void Interpret(const std::vector<Statements::Stmt>& statements);

  private:
    void Execute(const Statements::Stmt& stmt);

    Object::LoxObj Eval(const Expressions::Expr& expr);
    Object::LoxObj Eval(const Expressions::BinaryExprPtr& expr);
    Object::LoxObj Eval(const Expressions::GroupingExprPtr& expr);
    Object::LoxObj Eval(const Expressions::LiteralExprPtr& expr);
    Object::LoxObj Eval(const Expressions::UnaryExprPtr& expr);

    static bool IsEqual(const Object::LoxObj& objLeft,
                        const Object::LoxObj& objRight);

    static double
    PerformArithmeticOperation(const Lexer::TokenPtr& op,
                               const Object::LoxObj& objLeft,
                               const Object::LoxObj& objRight,
                               std::function<double(double, double)> func);
    static bool
    PerformLogicalOperation(const Lexer::TokenPtr& op,
                            const Object::LoxObj& objLeft,
                            const Object::LoxObj& objRight,
                            std::function<bool(double, double)> func);

    static double CheckNumberOperand(const Lexer::TokenPtr& op,
                                     const Object::LoxObj& obj);
    static std::pair<double, double>
    CheckNumberOperands(const Lexer::TokenPtr& op,
                        const Object::LoxObj& objLeft,
                        const Object::LoxObj& objRight);
};

} // namespace Loxpp::Interpreter