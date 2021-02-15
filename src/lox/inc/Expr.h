#pragma once

#include "Tokens.h"

#include <memory>
#include <type_traits>
#include <variant>
// TODO: better namespace
namespace Loxpp::Parser::Expressions {

/* Define the types of nodes in the AST and the fields associated with each
node. Defining a name and it's types results in creation of a POD struct that
consumes its arguments and a factory function to make an instance of the
Expr type. Example follows:

DefineExprOneField(ExampleExpression, string, foo) ->

struct ExampleExpression {
    string foo;
    ExampleExpression(string foo) : foo(std::move(foo)) {}
};

intline Expr MakeExampleExpression(string&& foo) {
    return std::make_unique<ExampleExpression>(std::move(foo));
}
*/
#define DefineExprOneField(NAME, FIELD1_TYPE, FIELD1_NAME)                     \
    struct NAME {                                                              \
        FIELD1_TYPE FIELD1_NAME;                                               \
        NAME(FIELD1_TYPE FIELD1_NAME) : FIELD1_NAME(std::move(FIELD1_NAME)) {} \
    };                                                                         \
    inline Expr Make##NAME(FIELD1_TYPE&& FIELD1_NAME) {                        \
        return std::make_unique<NAME>(std::move(FIELD1_NAME));                 \
    }

#define DefineExprTwoFields(NAME, FIELD1_TYPE, FIELD1_NAME, FIELD2_TYPE,       \
                            FIELD2_NAME)                                       \
    struct NAME {                                                              \
        FIELD1_TYPE FIELD1_NAME;                                               \
        FIELD2_TYPE FIELD2_NAME;                                               \
        NAME(FIELD1_TYPE FIELD1_NAME, FIELD2_TYPE FIELD2_NAME)                 \
            : FIELD1_NAME(std::move(FIELD1_NAME)),                             \
              FIELD2_NAME(std::move(FIELD2_NAME)) {}                           \
    };                                                                         \
    inline Expr Make##NAME(FIELD1_TYPE&& FIELD1_NAME,                          \
                           FIELD2_TYPE&& FIELD2_NAME) {                        \
        return std::make_unique<NAME>(std::move(FIELD1_NAME),                  \
                                      std::move(FIELD2_NAME));                 \
    }

#define DefineExprThreeFields(NAME, FIELD1_TYPE, FIELD1_NAME, FIELD2_TYPE,     \
                              FIELD2_NAME, FIELD3_TYPE, FIELD3_NAME)           \
    struct NAME {                                                              \
        FIELD1_TYPE FIELD1_NAME;                                               \
        FIELD2_TYPE FIELD2_NAME;                                               \
        FIELD3_TYPE FIELD3_NAME;                                               \
        NAME(FIELD1_TYPE FIELD1_NAME, FIELD2_TYPE FIELD2_NAME,                 \
             FIELD3_TYPE FIELD3_NAME)                                          \
            : FIELD1_NAME(std::move(FIELD1_NAME)),                             \
              FIELD2_NAME(std::move(FIELD2_NAME)),                             \
              FIELD3_NAME(std::move(FIELD3_NAME)) {}                           \
    };                                                                         \
    inline Expr Make##NAME(FIELD1_TYPE&& FIELD1_NAME,                          \
                           FIELD2_TYPE&& FIELD2_NAME,                          \
                           FIELD3_TYPE&& FIELD3_NAME) {                        \
        return std::make_unique<NAME>(std::move(FIELD1_NAME),                  \
                                      std::move(FIELD2_NAME),                  \
                                      std::move(FIELD3_NAME));                 \
    }

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
DefineExprThreeFields(BinaryExpr, Expr, left, Lexer::TokenPtr, op, Expr, right);

// GroupingExpr : ExprPtr expression
DefineExprOneField(GroupingExpr, Expr, expression);

// LiteralExpr : LiteralValue value
DefineExprOneField(LiteralExpr, Lexer::LiteralValue, value);

// UnaryExpr : Token op, ExprPtr right
DefineExprTwoFields(UnaryExpr, Lexer::TokenPtr, op, Expr, right);

} // namespace Loxpp::Parser::Expressions