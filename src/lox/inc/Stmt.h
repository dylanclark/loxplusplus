#pragma once

#include "CodeGen.h"
#include "Expr.h"
#include "Tokens.h"

#include <memory>
#include <type_traits>
#include <variant>

namespace Loxpp::Statements {

// Forward declare statement types
struct ExpressionStmt;
struct PrintStmt;

// As ptrs
using ExpressionStmtPtr = std::unique_ptr<ExpressionStmt>;
using PrintStmtPtr = std::unique_ptr<PrintStmt>;

// Main expression
using Stmt = std::variant<ExpressionStmtPtr, PrintStmtPtr>;

/* Define the structs */

// ExpressionStmt : Expr expression
DefineWithOneField(Stmt, ExpressionStmt, Expressions::Expr, expression);

// PrintStmt : Expr expression
DefineWithOneField(Stmt, PrintStmt, Expressions::Expr, expression);

} // namespace Loxpp::Statements