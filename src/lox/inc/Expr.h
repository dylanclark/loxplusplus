#pragma once

#include "Tokens.h"

#include <memory>

namespace Loxpp::Parser::Expressions {
// Marker interface
struct IExpr {
    virtual ~IExpr() = default;
};

#define DefineField(TYPE, NAME) TYPE NAME

#define DefineExprOneField(NAME, FIELD)                                        \
    struct NAME : public IExpr {                                               \
        FIELD;                                                                 \
        NAME(FIELD);                                                           \
    };

#define DefineExprTwoFields(NAME, FIELD1, FIELD2)                              \
    struct NAME : public IExpr {                                               \
        FIELD1;                                                                \
        FIELD2;                                                                \
        NAME(FIELD1, FIELD2);                                                  \
    };

#define DefineExprThreeFields(NAME, FIELD1, FIELD2, FIELD3)                    \
    struct NAME : public IExpr {                                               \
        FIELD1;                                                                \
        FIELD2;                                                                \
        FIELD3;                                                                \
        NAME(FIELD1, FIELD2, FIELD3);                                          \
    };

using ExprPtr = std::unique_ptr<IExpr>;

// BinaryExpr : ExprPtr left, Token op, ExprPtr right
DefineExprThreeFields(BinaryExpr, DefineField(ExprPtr, left),
                      DefineField(Lexer::Token, op),
                      DefineField(ExprPtr, right));

// GroupingExpr : ExprPtr expression
DefineExprOneField(GroupingExpr, DefineField(ExprPtr, expression));

// LiteralExpr : LiteralValue value
DefineExprOneField(LiteralExpr, DefineField(Lexer::LiteralValue, value));

// UnaryExpr : Token op, ExprPtr right
DefineExprTwoFields(UnaryExpr, DefineField(Lexer::Token, op),
                    DefineField(ExprPtr, right));

using ExprVariant =
    std::variant<BinaryExpr, GroupingExpr, LiteralExpr, UnaryExpr>;

} // namespace Loxpp::Parser::Expressions