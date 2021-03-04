#pragma once

#include <string>

// ローカル変数
struct LVar {
    std::string name;   // 変数名
    int offset;         // RBPからのオフセット

    LVar(const std::string& name, int offset)
        : name(name), offset(offset) { }
};
