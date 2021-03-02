#include "generate.hpp"
#include "Error.hpp"

std::ostream &generate(std::ostream &out, Node* node) {
    switch(node->kind) {
    case NodeKind::NOP:
        break;
    case NodeKind::NUMBER:
        out << "  push " << node->value << std::endl;
        break;
    case NodeKind::BLOCK:
        for (auto arg : node->args) {
            generate(out, arg);
            if (arg->kind != NodeKind::BLOCK && arg->kind != NodeKind::NOP) {
                out << "  pop rax" << std::endl;
            }
        }
        break;
    case NodeKind::ADD:
        generate(out, node->args.at(0));
        generate(out, node->args.at(1));
        out << "  pop rdi" << std::endl;
        out << "  pop rax" << std::endl;
        out << "  add rax, rdi" << std::endl;
        out << "  push rax" << std::endl;
        break;
    case NodeKind::SUB:
        generate(out, node->args.at(0));
        generate(out, node->args.at(1));
        out << "  pop rdi" << std::endl;
        out << "  pop rax" << std::endl;
        out << "  sub rax, rdi" << std::endl;
        out << "  push rax" << std::endl;
        break;
    case NodeKind::MUL:
        generate(out, node->args.at(0));
        generate(out, node->args.at(1));
        out << "  pop rdi" << std::endl;
        out << "  pop rax" << std::endl;
        out << "  imul rax, rdi" << std::endl;
        out << "  push rax" << std::endl;
        break;
    case NodeKind::DIV:
        generate(out, node->args.at(0));
        generate(out, node->args.at(1));
        out << "  pop rdi" << std::endl;
        out << "  pop rax" << std::endl;
        out << "  cqo" << std::endl;
        out << "  idiv rdi" << std::endl;
        out << "  push rax" << std::endl;
        break;
    case NodeKind::REM:
        generate(out, node->args.at(0));
        generate(out, node->args.at(1));
        out << "  pop rdi" << std::endl;
        out << "  pop rax" << std::endl;
        out << "  cqo" << std::endl;
        out << "  idiv rdi" << std::endl;
        out << "  push rdx" << std::endl;
        break;
    }
    return out;
}
