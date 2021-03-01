#include "Error.hpp"

std::string *Error::code_ptr = nullptr;

void Error::at(size_t char_number, const std::string& message) {
    if (code_ptr != nullptr && char_number < code_ptr->size()) {
        std::cerr << *code_ptr << std::endl;
        std::cerr << std::string(char_number, ' ') << std::endl;
        std::cerr << "^ " << std::endl;
    }
    std::cerr << message << std::endl;
    exit(1);
}

// void Error::_error_at() { }

// template <class T, class... Args>
// void Error::_error_at(const T& value, const Args&... args) {
//     std::cerr << value;
//     _error_at(args...);
// }
