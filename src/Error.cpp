#include "Error.hpp"

std::string *Error::code_ptr = nullptr;

void Error::at(size_t char_number, const std::string& message) {
    if (code_ptr != nullptr && 0 <= char_number) {
        std::cerr << *code_ptr << "\n";
        std::cerr << std::string(char_number, ' ') << "^ \n";
    }
    std::cerr << message << "\n";
    std::cerr << std::flush;
    exit(1);
}

// void Error::_error_at() { }

// template <class T, class... Args>
// void Error::_error_at(const T& value, const Args&... args) {
//     std::cerr << value;
//     _error_at(args...);
// }
