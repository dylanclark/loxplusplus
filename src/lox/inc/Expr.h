#pragma once

#include "Tokens.h"

#include <memory>

namespace Loxpp::Parser::Expressions {

#define DefineExprOneField(NAME, FIELD1_TYPE, FIELD1_NAME)                     \
    struct NAME {                                                              \
        FIELD1_TYPE FIELD1_NAME;                                               \
        NAME(FIELD1_TYPE FIELD1_NAME) : FIELD1_NAME(std::move(FIELD1_NAME)) {} \
    };                                                                         \
    inline ExprVariant Make##NAME(FIELD1_TYPE&& FIELD1_NAME) {                 \
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
    inline ExprVariant Make##NAME(FIELD1_TYPE&& FIELD1_NAME,                   \
                                  FIELD2_TYPE&& FIELD2_NAME) {                 \
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
    inline ExprVariant Make##NAME(FIELD1_TYPE&& FIELD1_NAME,                   \
                                  FIELD2_TYPE&& FIELD2_NAME,                   \
                                  FIELD3_TYPE&& FIELD3_NAME) {                 \
        return std::make_unique<NAME>(std::move(FIELD1_NAME),                  \
                                      std::move(FIELD2_NAME),                  \
                                      std::move(FIELD3_NAME));                 \
    }

struct BinaryExpr;
struct GroupingExpr;
struct LiteralExpr;
struct UnaryExpr;

using BinaryExprPtr = std::unique_ptr<BinaryExpr>;
using GroupingExprPtr = std::unique_ptr<GroupingExpr>;
using LiteralExprPtr = std::unique_ptr<LiteralExpr>;
using UnaryExprPtr = std::unique_ptr<UnaryExpr>;

using ExprVariant =
    std::variant<BinaryExprPtr, GroupingExprPtr, LiteralExprPtr, UnaryExprPtr>;

// BinaryExpr : ExprPtr left, Token op, ExprPtr right
DefineExprThreeFields(BinaryExpr, ExprVariant, left, Lexer::TokenPtr, op,
                      ExprVariant, right);

// GroupingExpr : ExprPtr expression
DefineExprOneField(GroupingExpr, ExprVariant, expression);

// LiteralExpr : LiteralValue value
DefineExprOneField(LiteralExpr, Lexer::LiteralValue, value);

// UnaryExpr : Token op, ExprPtr right
DefineExprTwoFields(UnaryExpr, Lexer::TokenPtr, op, ExprVariant, right);

} // namespace Loxpp::Parser::Expressions