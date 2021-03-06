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

int LAndNumber = 0;
int LOrNumber = 0;
int LIfNumber = 0;
int LWhileNumber = 0;

std::ostream &generate(std::ostream &out, Node* node) {
    int LAndNumberNow = LAndNumber;
    int LOrNumberNow = LOrNumber;
    int LIfNumberNow = LIfNumber;
    int LWhileNumberNow = LWhileNumber;

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
    case NodeKind::RETURN:
        generate(out, node->args.at(0));
        out << "  pop rax\n";
        out << "  mov rsp, rbp\n";
        out << "  pop rbp\n";
        out << "  ret\n";
        break;
    case NodeKind::IF:
        LIfNumber++;
        generate(out, node->args.at(0));
        out << "  pop rax\n";
        out << "  cmp rax, 0\n";
        if (node->args.size() == 2) {
            out << "  je  .LIfEnd" << LIfNumberNow << "\n";
            generate(out, node->args.at(1));
            out << ".LIfEnd" << LIfNumberNow << ":\n";
        } else {
            out << "  je  .LIfElse" << LIfNumberNow << "\n";
            generate(out, node->args.at(1));
            out << "  jmp  .LIfEnd" << LIfNumberNow << "\n";
            out << ".LIfElse" << LIfNumberNow << ":\n";
            generate(out, node->args.at(2));
            out << ".LIfEnd" << LIfNumberNow << ":\n";
        }
        break;
    case NodeKind::WHILE:
        LWhileNumber++;
        out << ".LWhileBegin" << LWhileNumberNow << ":\n";
        generate(out, node->args.at(0));
        out << "  pop rax\n";
        out << "  cmp rax, 0\n";
        if (node->args.size() == 2) {
            out << "  je .LWhileEnd" << LWhileNumberNow << "\n";
        } else {
            out << "  je .LWhileElse" << LWhileNumberNow << "\n";
        }
        generate(out, node->args.at(1));
        out << "  jmp .LWhileBegin" << LWhileNumberNow << "\n";
        if (node->args.size() == 3) {
            out << ".LWhileElse" << LWhileNumberNow << ":\n";
            generate(out, node->args.at(2));
        }
        out << ".LWhileEnd" << LWhileNumberNow << ":\n";
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
    case NodeKind::AND:
        LAndNumber++;
        for (auto arg : node->args) {
            generate(out, arg);
            out << "  pop rax\n";
            out << "  cmp rax, 0\n";
            out << "  je .LAndFalse" << LAndNumberNow << "\n";
        }
        out << "  mov rax, 1\n";
        out << "  jmp .LAndEnd" << LAndNumberNow << "\n";
        out << ".LAndFalse" << LAndNumberNow << ":\n";
        out << "  mov rax, 0\n";
        out << ".LAndEnd" << LAndNumberNow << ":\n";
        out << "  movzx rax, al\n";
        out << "  push rax\n";
        break;
    case NodeKind::OR:
        LOrNumber++;
        for (auto arg : node->args) {
            generate(out, arg);
            out << "  pop rax\n";
            out << "  cmp rax, 0\n";
            out << "  jne .LOrTrue" << LOrNumberNow << "\n";
        }
        out << "  mov rax, 0\n";
        out << "  jmp .LOrEnd" << LOrNumberNow << "\n";
        out << ".LOrTrue" << LOrNumberNow << ":\n";
        out << "  mov rax, 1\n";
        out << ".LOrEnd" << LOrNumberNow << ":\n";
        out << "  movzx rax, al\n";
        out << "  push rax\n";
        break;
    }
    return out;
}
