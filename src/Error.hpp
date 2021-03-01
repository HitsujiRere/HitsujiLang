#pragma once

#include <iostream>
#include <string>

class Error {
public:
    // コードのポインタ
    static std::string *code_ptr;

    // エラー箇所を報告する
    static void at(size_t char_number, const std::string& message);
    // template<class... Args>
    // static void at(size_t char_number, const Args&... args);

private:
    Error() {};
    ~Error() {};
    Error(const Error &x) { };
    Error &operator=(const Error &) { return *this; };

//     void _error_at();

//     template <class T, class... Args>
//     static void _error_at(const T& value, const Args&... args);
};
