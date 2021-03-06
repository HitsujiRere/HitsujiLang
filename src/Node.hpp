#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Token.hpp"
#include "LVar.hpp"

// トークンの種類
enum class NodeKind {
    NOP,    // 何もしない
    ADD,    // +
    SUB,    // -
    MUL,    // *
    DIV,    // /
    REM,    // %
    EQ,     // ==
    NEQ,    // !=
    LT,     // <
    LEQ,    // <=
    AND,    // &&
    OR,     // ||
    ASSIGN, // =
    RETURN, // return
    IF,     // if
    WHILE,  // while
    NUMBER, // 整数
    LVAR,   // ローカル変数
    BLOCK,  // ブロック
};

// トークン型
struct Node {
    NodeKind kind;              // ノードの型
    int value;                  // kindがNUMBERのとき，値
    std::vector<Node *> args;   // 子
    int offset;                 // kindがLVARのとき，オフセット

    Node(NodeKind kind) : kind(kind) { }
};

// program    = stmt*
// stmt       = expr ";"
//            | control
//            | "return" expr ";"
// control    = "{" stmt* "}"
//            | "if" expr stmt ("else" stmt)?
//            | "while" expr stmt ("else" stmt)?
// expr       = assign
// assign     = logical ("=" assign)?
// logical    = comp ("&&" comp | "||" comp);
// comp       = add ("==" add | "!=" add | "<" add | "<=" add | ">" add | ">=" add)*
// add        = mul ("+" mul | "-" mul)*
// mul        = unary ("*" unary | "/" unary)*
// unary      = ("+" | "-")? primary
// primary    = "(" expr ")" | num | ident
Node *program(std::vector<Token>::const_iterator& token_itr);
Node *stmt(std::vector<Token>::const_iterator& token_itr);
Node *control(std::vector<Token>::const_iterator& token_itr);
Node *expr(std::vector<Token>::const_iterator& token_itr);
Node *assign(std::vector<Token>::const_iterator& token_itr);
Node *logical(std::vector<Token>::const_iterator& token_itr);
Node *comp(std::vector<Token>::const_iterator& token_itr);
Node *add(std::vector<Token>::const_iterator& token_itr);
Node *mul(std::vector<Token>::const_iterator& token_itr);
Node *unary(std::vector<Token>::const_iterator& token_itr);
Node *primary(std::vector<Token>::const_iterator& token_itr);
