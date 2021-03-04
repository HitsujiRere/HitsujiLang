// #pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Token.hpp"
#include "Node.hpp"
#include "generate.hpp"

// コード
std::string code;

// トークン
std::vector<Token> tokens;

// ノード
Node* node;

int main(int argc, char const *argv[]);
