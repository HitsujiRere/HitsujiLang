#include "HitsujiLang.hpp"
#include "Error.hpp"

int main(int argc, char const *argv[])
{
    Error::code_ptr = &code;

    if (argc == 1) {
        std::cerr << "no input files" << std::endl;
        return 1;
    }

    code = std::string(argv[1]);

    tokens = tokenize(code);

    auto tokens_head = tokens.cbegin();
    node = program(tokens_head);

    std::cout << ".intel_syntax noprefix\n";
    std::cout << ".globl main\n";
    std::cout << "main:\n";
    std::cout << "  push rbp\n";
    std::cout << "  mov rbp, rsp\n";
    std::cout << "  sub rsp, 208\n";

    generate(std::cout, node);
    
    std::cout << "  mov rsp, rbp\n";
    std::cout << "  pop rbp\n";
    std::cout << "  ret\n";

    return 0;
}
