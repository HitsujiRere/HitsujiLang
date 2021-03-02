#include "generate.hpp"
#include "Error.hpp"

std::ostream &generate_lvalue(std::ostream &out, Node* node) {
    if (node->kind != NodeKind::LVAR) {
        Error::at(-1, "代入の左辺値が変数ではありません");
    }

    out << "  mov rax, rbp" << std::endl;
    out << "  sub rax, " << node->offset << std::endl;
    out << "  push rax" << std::endl;
    
    return out;
}

std::ostream &generate(std::ostream &out, Node* node) {
    switch(node->kind) {
    case NodeKind::NOP:
        break;
    case NodeKind::NUMBER:
        out << "  push " << node->value << std::endl;
        break;
    case NodeKind::LVAR:
        generate_lvalue(out, node);
        out << "  pop rax" << std::endl;
        out << "  mov rax, [rax]" << std::endl;
        out << "  push rax" << std::endl;
        break;
    case NodeKind::BLOCK:
        for (auto arg : node->args) {
            generate(out, arg);
            if (arg->kind != NodeKind::BLOCK && arg->kind != NodeKind::NOP) {
                out << "  pop rax" << std::endl;
            }
        }
        break;
    case NodeKind::ASSIGN:
        generate_lvalue(out, node->args.at(0));
        generate(out, node->args.at(1));
        out << "  pop rdi" << std::endl;
        out << "  pop rax" << std::endl;
        out << "  mov [rax], rdi" << std::endl;
        out << "  push rdi" << std::endl;
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
    case NodeKind::EQ:
        generate(out, node->args.at(0));
        generate(out, node->args.at(1));
        out << "  pop rdi" << std::endl;
        out << "  pop rax" << std::endl;
        out << "  cmp rax, rdi" << std::endl;
        out << "  sete al" << std::endl;
        out << "  movzb rax, al" << std::endl;
        out << "  push rax" << std::endl;
        break;
    case NodeKind::NEQ:
        generate(out, node->args.at(0));
        generate(out, node->args.at(1));
        out << "  pop rdi" << std::endl;
        out << "  pop rax" << std::endl;
        out << "  cmp rax, rdi" << std::endl;
        out << "  setne al" << std::endl;
        out << "  movzb rax, al" << std::endl;
        out << "  push rax" << std::endl;
        break;
    case NodeKind::LT:
        generate(out, node->args.at(0));
        generate(out, node->args.at(1));
        out << "  pop rdi" << std::endl;
        out << "  pop rax" << std::endl;
        out << "  cmp rax, rdi" << std::endl;
        out << "  setl al" << std::endl;
        out << "  movzb rax, al" << std::endl;
        out << "  push rax" << std::endl;
        break;
    case NodeKind::LEQ:
        generate(out, node->args.at(0));
        generate(out, node->args.at(1));
        out << "  pop rdi" << std::endl;
        out << "  pop rax" << std::endl;
        out << "  cmp rax, rdi" << std::endl;
        out << "  setle al" << std::endl;
        out << "  movzb rax, al" << std::endl;
        out << "  push rax" << std::endl;
        break;
    }
    return out;
}
