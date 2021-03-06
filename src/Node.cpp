#include "Node.hpp"
#include "Error.hpp"

// ローカル変数
std::map<std::string, LVar> lvars;

// オフセット合計
int next_offset = 0;

bool is_reserved(const std::vector<Token>::const_iterator& token_itr, const std::string& txt) {
    return token_itr->kind == TokenKind::RESERVED && token_itr->txt == txt;
}

bool is_control_syntax(const std::vector<Token>::const_iterator& token_itr) {
    for (const auto& control_txt : { "{", "if", }) {
        if (control_txt == token_itr->txt) {
            return true;
        }
    }
    return false;
}

int get_offset(const std::vector<Token>::const_iterator& token_itr, const std::string& name) {
    auto lvar_itr = lvars.find(name);

    if (lvar_itr == lvars.end()) {
        // Error::at(token_itr->pos, "不明な変数です");
        LVar lvar(name, next_offset);
        next_offset += 8;
        lvars.emplace(name, lvar);
        return lvar.offset;
    }

    return lvar_itr->second.offset;
}

Node *program(std::vector<Token>::const_iterator& token_itr) {
    Node *node = new Node(NodeKind::BLOCK);
    while (token_itr->kind != TokenKind::END) {
        node->args.push_back(stmt(token_itr));
    }
    return node;
}

Node *stmt(std::vector<Token>::const_iterator& token_itr) {
    if (is_reserved(token_itr, ";")) {
        token_itr++;
        return new Node(NodeKind::NOP);
    } else if (is_reserved(token_itr, "return")) {
        token_itr++;

        Node *node = new Node(NodeKind::RETURN);
        node->args.push_back(expr(token_itr));

        if (!is_reserved(token_itr, ";")) {
            Error::at(token_itr->pos, "';'ではありません");
        }
        token_itr++;

        return node;
    } else if (is_control_syntax(token_itr)) {
        return control(token_itr);
    } else {
        Node *node = expr(token_itr);

        if (!is_reserved(token_itr, ";")) {
            Error::at(token_itr->pos, "';'ではありません");
        }
        token_itr++;

        return node;
    }
}

Node *control(std::vector<Token>::const_iterator& token_itr) {
    if (is_reserved(token_itr, "{")) {
        token_itr++;

        Node *block_node = new Node(NodeKind::BLOCK);
        while (!is_reserved(token_itr, "}")) {
            block_node->args.push_back(stmt(token_itr));
        }
        token_itr++;

        return block_node;
    } else if (is_reserved(token_itr, "if")) {
        token_itr++;

        Node *if_node = new Node(NodeKind::IF);
        if_node->args.push_back(expr(token_itr));
        if_node->args.push_back(stmt(token_itr));

        if (is_reserved(token_itr, "else")) {
            token_itr++;

            if_node->args.push_back(stmt(token_itr));
        }

        return if_node;
    } else {
        Error::at(token_itr->pos, "制御構文ではありません");
        return nullptr;
    }
}

Node *expr(std::vector<Token>::const_iterator& token_itr) {
    return assign(token_itr);
}

Node *assign(std::vector<Token>::const_iterator& token_itr) {
    Node *node = logical(token_itr);

    if (is_reserved(token_itr, "=")) {
        token_itr++;
        Node *ass = new Node(NodeKind::ASSIGN);
        ass->args.push_back(node);
        ass->args.push_back(assign(token_itr));
        return ass;
    }

    return node;
}

Node *logical(std::vector<Token>::const_iterator& token_itr) {
    Node *node = comp(token_itr);
    Node *head;

    while (true) {
        if (is_reserved(token_itr, "&&")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::AND);
            expr_node->args.push_back(node);
            expr_node->args.push_back(comp(token_itr));
            node = expr_node;
        } else if (is_reserved(token_itr, "||")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::OR);
            expr_node->args.push_back(node);
            expr_node->args.push_back(comp(token_itr));
            node = expr_node;
        } else {
            return node;
        }
    }
}

Node *comp(std::vector<Token>::const_iterator& token_itr) {
    Node *and_node = new Node(NodeKind::AND);
    Node *left_node = add(token_itr);

    while (true) {
        if (is_reserved(token_itr, "==")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::EQ);
            Node *right_node = add(token_itr);
            expr_node->args = {left_node, right_node};
            and_node->args.push_back(expr_node);
            left_node = right_node;
        } else if (is_reserved(token_itr, "!=")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::NEQ);
            Node *right_node = add(token_itr);
            expr_node->args = {left_node, right_node};
            and_node->args.push_back(expr_node);
            left_node = right_node;
        } else if (is_reserved(token_itr, "<")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::LT);
            Node *right_node = add(token_itr);
            expr_node->args = {left_node, right_node};
            and_node->args.push_back(expr_node);
            left_node = right_node;
        } else if (is_reserved(token_itr, ">")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::LT);
            Node *right_node = add(token_itr);
            expr_node->args = {right_node, left_node};
            and_node->args.push_back(expr_node);
            left_node = right_node;
        } else if (is_reserved(token_itr, "<=")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::LEQ);
            Node *right_node = add(token_itr);
            expr_node->args = {left_node, right_node};
            and_node->args.push_back(expr_node);
            left_node = right_node;
        } else if (is_reserved(token_itr, ">=")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::LEQ);
            Node *right_node = add(token_itr);
            expr_node->args = {right_node, left_node};
            and_node->args.push_back(expr_node);
            left_node = right_node;
        } else {
            return and_node->args.empty() ? left_node : and_node;
        }
    }
}

Node *add(std::vector<Token>::const_iterator& token_itr) {
    Node *node = mul(token_itr);

    while (true) {
        if (is_reserved(token_itr, "+")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::ADD);
            expr_node->args.push_back(node);
            expr_node->args.push_back(mul(token_itr));
            node = expr_node;
        } else if (is_reserved(token_itr, "-")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::SUB);
            expr_node->args.push_back(node);
            expr_node->args.push_back(mul(token_itr));
            node = expr_node;
        } else {
            return node;
        }
    }
}

Node *mul(std::vector<Token>::const_iterator& token_itr) {
    Node *node = unary(token_itr);

    while (true) {
        if (is_reserved(token_itr, "*")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::MUL);
            expr_node->args.push_back(node);
            expr_node->args.push_back(unary(token_itr));
            node = expr_node;
        } else if (is_reserved(token_itr, "/")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::DIV);
            expr_node->args.push_back(node);
            expr_node->args.push_back(unary(token_itr));
            node = expr_node;
        } else if (is_reserved(token_itr, "%")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::REM);
            expr_node->args.push_back(node);
            expr_node->args.push_back(unary(token_itr));
            node = expr_node;
        } else {
            return node;
        }
    }
}

Node *unary(std::vector<Token>::const_iterator& token_itr) {
    if (is_reserved(token_itr, "+")) {
        token_itr++;
        return primary(token_itr);
    } else if (is_reserved(token_itr, "-")) {
        token_itr++;
        Node *node = new Node(NodeKind::SUB);
        Node *number_node = new Node(NodeKind::NUMBER);
        number_node->value = 0;
        node->args.push_back(number_node);
        node->args.push_back(primary(token_itr));
        return node;
    }

    return primary(token_itr);
}

Node *primary(std::vector<Token>::const_iterator& token_itr) {
    if (is_reserved(token_itr, "(")) {
        token_itr++;
        Node *node = expr(token_itr);
        if (!is_reserved(token_itr, ")")) {
            Error::at(token_itr->pos, "')'ではありません");
        }
        token_itr++;
        return node;
    } else if (token_itr->kind == TokenKind::NUMBER) {
        Node *node = new Node(NodeKind::NUMBER);
        node->value = token_itr->value;
        token_itr++;
        return node;
    } else if (token_itr->kind == TokenKind::IDENT) {
        Node *node = new Node(NodeKind::LVAR);
        node->offset = get_offset(token_itr, token_itr->txt);
        token_itr++;
        return node;
    } else {
        Error::at(token_itr->pos, "'('または数字，識別子ではありません");
        return nullptr;
    }
}
