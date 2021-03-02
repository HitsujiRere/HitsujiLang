#include "HitsujiLang.hpp"
#include "Error.hpp"

int main(int argc, char const *argv[])
{
    Error::code_ptr = &code;

    if (argc == 1) {
        std::cerr << "no input files" << std::endl;
        return 1;
    }

    // code = getCode(argv[1]);

    // for (size_t i = 0; i < code.size(); i++) {
    //     std::cout << i << " | " << code.at(i) << std::endl;
    // }

    code = std::string(argv[1]);

    tokens = tokenize(code);

    auto tokens_head = tokens.cbegin();
    node = program(tokens_head);

    std::cout << ".intel_syntax noprefix" << std::endl;
    std::cout << ".globl main" << std::endl;
    std::cout << "main:" << std::endl;

    generate(std::cout, node);
    
    std::cout << "  ret" << std::endl;

    return 0;
}
