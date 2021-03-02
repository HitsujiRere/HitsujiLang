#include "generate.hpp"
#include "Error.hpp"

std::ostream &generate_lvalue(std::ostream &out, Node* node) {
    if (node->kind != NodeKind::LVAR) {
        Error::at(-1, "代入の左辺値が変数ではありません");
    }

    out << "  mov rax, rbp\n";
    out << "  sub rax, " << node->offset << "\n";
    out << "  push rax\n";
    
    return out;
}

std::ostream &generate(std::ostream &out, Node* node) {
    switch(node->kind) {
    case NodeKind::NOP:
        break;
    case NodeKind::NUMBER:
        out << "  push " << node->value << "\n";
        break;
    case NodeKind::LVAR:
        generate_lvalue(out, node);
        out << "  pop rax\n";
        out << "  mov rax, [rax]\n";
        out << "  push rax\n";
        break;
    case NodeKind::BLOCK:
        for (auto arg : node->args) {
            generate(out, arg);
            if (arg->kind != NodeKind::BLOCK && arg->kind != NodeKind::NOP) {
                out << "  pop rax\n";
            }
        }
        break;
    case NodeKind::ASSIGN:
        generate_lvalue(out, node->args.at(0));
        generate(out, node->args.at(1));
        out << "  pop rdi\n";
        out << "  pop rax\n";
        out << "  mov [rax], rdi\n";
        out << "  push rdi\n";
        break;
    case NodeKind::ADD:
        generate(out, node->args.at(0));
        generate(out, node->args.at(1));
        out << "  pop rdi\n";
        out << "  pop rax\n";
        out << "  add rax, rdi\n";
        out << "  push rax\n";
        break;
    case NodeKind::SUB:
        generate(out, node->args.at(0));
        generate(out, node->args.at(1));
        out << "  pop rdi\n";
        out << "  pop rax\n";
        out << "  sub rax, rdi\n";
        out << "  push rax\n";
        break;
    case NodeKind::MUL:
        generate(out, node->args.at(0));
        generate(out, node->args.at(1));
        out << "  pop rdi\n";
        out << "  pop rax\n";
        out << "  imul rax, rdi\n";
        out << "  push rax\n";
        break;
    case NodeKind::DIV:
        generate(out, node->args.at(0));
        generate(out, node->args.at(1));
        out << "  pop rdi\n";
        out << "  pop rax\n";
        out << "  cqo\n";
        out << "  idiv rdi\n";
        out << "  push rax\n";
        break;
    case NodeKind::REM:
        generate(out, node->args.at(0));
        generate(out, node->args.at(1));
        out << "  pop rdi\n";
        out << "  pop rax\n";
        out << "  cqo\n";
        out << "  idiv rdi\n";
        out << "  push rdx\n";
        break;
    case NodeKind::EQ:
        generate(out, node->args.at(0));
        generate(out, node->args.at(1));
        out << "  pop rdi\n";
        out << "  pop rax\n";
        out << "  cmp rax, rdi\n";
        out << "  sete al\n";
        out << "  movzb rax, al\n";
        out << "  push rax\n";
        break;
    case NodeKind::NEQ:
        generate(out, node->args.at(0));
        generate(out, node->args.at(1));
        out << "  pop rdi\n";
        out << "  pop rax\n";
        out << "  cmp rax, rdi\n";
        out << "  setne al\n";
        out << "  movzb rax, al\n";
        out << "  push rax\n";
        break;
    case NodeKind::LT:
        generate(out, node->args.at(0));
        generate(out, node->args.at(1));
        out << "  pop rdi\n";
        out << "  pop rax\n";
        out << "  cmp rax, rdi\n";
        out << "  setl al\n";
        out << "  movzb rax, al\n";
        out << "  push rax\n";
        break;
    case NodeKind::LEQ:
        generate(out, node->args.at(0));
        generate(out, node->args.at(1));
        out << "  pop rdi\n";
        out << "  pop rax\n";
        out << "  cmp rax, rdi\n";
        out << "  setle al\n";
        out << "  movzb rax, al\n";
        out << "  push rax\n";
        break;
    }
    return out;
}
