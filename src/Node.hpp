#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Token.hpp"

// トークンの種類
enum class NodeKind {
    NOP,    // 何もしない
    ADD,    // +
    SUB,    // -
    MUL,    // *
    DIV,    // /
    REM,    // %
    NUMBER, // 整数
    BLOCK,  // ブロック
};

// トークン型
struct Node {
    NodeKind kind;
    int value;
    std::vector<Node *> args;

    Node(NodeKind kind) : kind(kind) { }
};

Node *program(std::vector<Token>::const_iterator& token_itr);
