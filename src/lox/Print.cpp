#include <loxpp_pch.h>

#include <Expr.h>
#include <Print.h>
#include <Tokens.h>
#include <VisitHelpers.h>

using namespace Loxpp;
using namespace Loxpp::Lexer;
using namespace Loxpp::Parser;
using namespace Loxpp::Parser::Expressions;

namespace Literals {
constexpr auto Space{" "};
constexpr auto TokenName{"Token"};
constexpr auto Colon{":"};
constexpr auto OpenBracket{"{"};
constexpr auto CloseBracket{"}"};
constexpr auto Type{"Type"};
constexpr auto Lex{"Lex"};
constexpr auto Literal{"Literal"};
constexpr auto Tab{"\t"};
} // namespace Literals

void Parenthesize(std::ostream& stream, const std::string& name,
                  const Expr& expr) {
    stream << "(" << name << " " << expr << ")";
}

void Parenthesize(std::ostream& stream, const std::string& name,
                  const Expr& exprOne, const Expr& exprTwo) {
    stream << "(" << name << " " << exprOne << " " << exprTwo << ")";
}
std::ostream& operator<<(std::ostream& stream, const Expr& expr) {
    using namespace Lexer;
    std::visit(
        overloaded{// Define << overload for each type of the variant here
                   [&stream](const BinaryExprPtr& binaryExpr) {
                       Parenthesize(stream, binaryExpr->op->GetLexeme(),
                                    binaryExpr->left, binaryExpr->right);
                   },
                   [&stream](const GroupingExprPtr& groupingExpr) {
                       Parenthesize(stream, "group", groupingExpr->expression);
                   },
                   [&stream](const LiteralExprPtr& literalExpr) {
                       stream << literalExpr->value;
                   },
                   [&stream](const UnaryExprPtr& unaryExpr) {
                       Parenthesize(stream, unaryExpr->op->GetLexeme(),
                                    unaryExpr->right);
                   }},
        expr);
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Token& token) {
    using namespace Literals;
    // Opening : "Token { "
    stream << TokenName << Space << OpenBracket << Space;
    // Type and lexeme " Type: <type>\tLexeme: <lexeme>\t"
    stream << Type << Colon << Space << ToString(token.GetType()) << Tab << Lex
           << Colon << Space << token.GetLexeme() << Tab;
    // Literal value if present
    if (token.GetLiteral().has_value()) {
        stream << Literal << Colon << Space;
        std::visit([&stream](const auto& variant) { stream << variant; },
                   token.GetLiteral().value());
        stream << Tab;
    }
    // Closing
    stream << CloseBracket << std::endl;
    return stream;
}

std::ostream& operator<<(std::ostream& stream,
                         const Lexer::LiteralValue& value) {
    std::visit(overloaded{
                   [&stream](const std::string& s) { stream << s; },
                   [&stream](double d) { stream << d; },
                   [&stream](bool b) { stream << b; },
                   [&stream](std::monostate) { stream << "[null]"; },
               },
               value);
    return stream;
}