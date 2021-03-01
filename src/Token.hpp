#pragma once

#include <iostream>
#include <string>
#include <vector>

// トークンの種類
enum class TokenKind {
    RESERVED,   // 記号
    IDENT,      // 識別子
    NUM,        // 整数トークン
};

// トークン型
struct Token {
    TokenKind kind;     // トークンの型
    int value;          // kindがTK_NUMの場合、その数値
    std::string txt;    // トークン文字列
    size_t pos;         // 位置
};

// 記号
const std::vector<std::string> reserves = {
    "==", "!=", "<=", ">=",
    "**", "//", "&&", "||", "^^",
    "(", ")", "{", "}", "<", ">",
    ";", ",", "=", "+", "-", "*", "/", "&" "|", "^",
};

// 識別子のような記号
const std::vector<std::string> reserves_ident = {
    "def",
    "return",
    "if",
    "else",
    "while",
    "for",
    "to",
    "downto",
};

// トークナイズをする
std::vector<Token> tokenize(const std::string& code);
