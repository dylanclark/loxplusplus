# Crafting interpreters notes

(TODO: Come through and clean this up. Hope to organize and make it helpful. For now it's just a running list of notes to self as I work through the book)

## Chapter 4
- Use streams instead of strings for running?
- Java and C++ substr methods are different! start,end in java and start,len in c++!
- literals are doubles or strings - use variant

## Chapter 5

- The lexical grammar from chapter 1 is a regular language with no semantic meaning
- In this chapter we're creating a syntactic grammer. The 'alphabet' is the tokens here. 
- We'll be parsing the lexical grammar into syntactic, which is context-free
- CFG is a finite set of rules
    - Strings created by following rules are 'derivations'
    - Rules are called 'productions' because they produce strings in the grammer
    - Each production has a 'head' (it's name) and a body, which describes what it generates
    - Body is a list of symbols
        - Terminal symbols are letters from the grammars alphabet. In our case, that means lexical tokens
        - Nonterminal symbol is a named reference to another rule in the grammar - it means to follow that rules
- CFG often represented in Backus-Naur form. 
    - Our bnf: `<rule name> -> <symbol> | <symbol> | ( <symbol> | <symbol> ) | <symbol>*;`
        - pipe `|` for multiple productions
        - parens `()` for grouping in middle of production
        - `*` for recursion (repeat 0 or more times)
        - `+` for recursion (repeat 1 or more times)
        - `?` for optional production (repeat 0 or 1 time)

- When a rule has multiple productions, pick one arbitrarily. Allows a small grammar to encode a 
combinatorially larger set of strings

- This chapter: literals, unary, binary, parens
```
expression     → literal
               | unary
               | binary
               | grouping ;

literal        → NUMBER | STRING | "true" | "false" | "nil" ;
grouping       → "(" expression ")" ;
unary          → ( "-" | "!" ) expression ;
binary         → expression operator expression ;
operator       → "==" | "!=" | "<" | "<=" | ">" | ">="
               | "+"  | "-"  | "*" | "/" ;
```
- skip impl of astprinter, as we need to build the tree first ...
- 
## Chapter 6

- We need well-defined precedence nd associativity to avoid amiguity. Without it, `6 / 3 - 1` could evaluate to `(6/3) - 1 = 1` or `6 / (3 - 1) = 3`.
- Same precedence rules as C:
  
  | Name       | Operators            | Associativity |
  | ---------- | -------------------- | ------------- |
  | Equality   | `==`,`!=`            | Left          |
  | Comparison | `>`, `>=`, `<`, `<=` | Left          |
  | Term       | `-`, `+`             | Left          |
  | Factor     | `/`, `*`             | Left          |
  | Unary      | `!` , `-`            | Right         |

- We need to stratify the grammar so ensure it follows precedence rules:
  
```
expression     → equality ;
equality       → comparison ( ( "!=" | "==" ) comparison )* ;
comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
term           → factor ( ( "-" | "+" ) factor )* ;
factor         → unary ( ( "/" | "*" ) unary )* ;
unary          → ( "!" | "-" ) unary
               | primary ;
primary        → NUMBER | STRING | "true" | "false" | "nil"
               | "(" expression ")" ;
```

- Parsing technique of choise is "recursive descent". It is a top-down parsing technique that literally translates the grammar's rules into imperitive code. Each rule is a function.
- notes on variant impl and codegen
- overloadeding << for types for printing 

## Chapter 7

- Visitor pattern for matching types and recursively evaluating
- functional approach to binary ops
- opportunity to templatize it and make it even smaller

## Chapter 8

- Introducing statements, our grammar expands to:

```
program        → statement* EOF ; (new)
statement      → exprStmt
               | printStmt ; (new) 
exprStmt       → expression ";" ; (new)
printStmt      → "print" expression ";" ; (new)
expression     → equality ;
equality       → comparison ( ( "!=" | "==" ) comparison )* ;
comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
term           → factor ( ( "-" | "+" ) factor )* ;
factor         → unary ( ( "/" | "*" ) unary )* ;
unary          → ( "!" | "-" ) unary
               | primary ;
primary        → NUMBER | STRING | "true" | "false" | "nil"
               | "(" expression ")" ;
```

- Expressions and statements are disjoint so we impl separately
