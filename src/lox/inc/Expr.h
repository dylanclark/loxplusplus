#pragma once

#include "CodeGen.h"
#include "Tokens.h"

#include <memory>
#include <type_traits>
#include <variant>

namespace Loxpp::Expressions {

// Forward declare expression types
struct BinaryExpr;
struct GroupingExpr;
struct LiteralExpr;
struct UnaryExpr;

// As ptrs
using BinaryExprPtr = std::unique_ptr<BinaryExpr>;
using GroupingExprPtr = std::unique_ptr<GroupingExpr>;
using LiteralExprPtr = std::unique_ptr<LiteralExpr>;
using UnaryExprPtr = std::unique_ptr<UnaryExpr>;

// Main expression
using Expr =
    std::variant<BinaryExprPtr, GroupingExprPtr, LiteralExprPtr, UnaryExprPtr>;

/* Define the structs */

// BinaryExpr : ExprPtr left, Token op, ExprPtr right
DefineWithThreeFields(Expr, BinaryExpr, Expr, left, Lexer::TokenPtr, op, Expr,
                      right);

// GroupingExpr : ExprPtr expression
DefineWithOneField(Expr, GroupingExpr, Expr, expression);

// LiteralExpr : LiteralValue value
DefineWithOneField(Expr, LiteralExpr, Lexer::LiteralValue, value);

// UnaryExpr : Token op, ExprPtr right
DefineWithTwoFields(Expr, UnaryExpr, Lexer::TokenPtr, op, Expr, right);

} // namespace Loxpp::Expressions