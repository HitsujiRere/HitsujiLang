#include "Node.hpp"
#include "Error.hpp"

bool isReserved(const std::vector<Token>::const_iterator& token_itr, const std::string& txt) {
    return token_itr->kind == TokenKind::RESERVED && token_itr->txt == txt;
}

Node *program(std::vector<Token>::const_iterator& token_itr) {
    Node *node = new Node(NodeKind::BLOCK);
    while (token_itr->kind != TokenKind::END) {
        node->args.push_back(stmt(token_itr));
    }
    return node;
}

Node *stmt(std::vector<Token>::const_iterator& token_itr) {
    Node *node = expr(token_itr);

    if (!isReserved(token_itr, ";")) {
        Error::at(token_itr->pos, "';'ではありません");
    }
    token_itr++;

    return node;
}

Node *expr(std::vector<Token>::const_iterator& token_itr) {
    return assign(token_itr);
}

Node *assign(std::vector<Token>::const_iterator& token_itr) {
    Node *node = comp(token_itr);

    if (isReserved(token_itr, "=")) {
        token_itr++;
        Node *ass = new Node(NodeKind::ASSIGN);
        ass->args.push_back(node);
        ass->args.push_back(assign(token_itr));
        return ass;
    }

    return node;
}

Node *comp(std::vector<Token>::const_iterator& token_itr) {
    Node *node = add(token_itr);

    while (true) {
        if (isReserved(token_itr, "==")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::EQ);
            expr_node->args.push_back(node);
            expr_node->args.push_back(add(token_itr));
            node = expr_node;
        } else if (isReserved(token_itr, "!=")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::NEQ);
            expr_node->args.push_back(node);
            expr_node->args.push_back(add(token_itr));
            node = expr_node;
        } else if (isReserved(token_itr, "<")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::LT);
            expr_node->args.push_back(node);
            expr_node->args.push_back(add(token_itr));
            node = expr_node;
        } else if (isReserved(token_itr, ">")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::LT);
            expr_node->args.push_back(add(token_itr));
            expr_node->args.push_back(node);
            node = expr_node;
        } else if (isReserved(token_itr, "<=")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::LEQ);
            expr_node->args.push_back(node);
            expr_node->args.push_back(add(token_itr));
            node = expr_node;
        } else if (isReserved(token_itr, ">=")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::LEQ);
            expr_node->args.push_back(add(token_itr));
            expr_node->args.push_back(node);
            node = expr_node;
        } else {
            return node;
        }
    }
}

Node *add(std::vector<Token>::const_iterator& token_itr) {
    Node *node = mul(token_itr);

    while (true) {
        if (isReserved(token_itr, "+")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::ADD);
            expr_node->args.push_back(node);
            expr_node->args.push_back(mul(token_itr));
            node = expr_node;
        } else if (isReserved(token_itr, "-")) {
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
        if (isReserved(token_itr, "*")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::MUL);
            expr_node->args.push_back(node);
            expr_node->args.push_back(unary(token_itr));
            node = expr_node;
        } else if (isReserved(token_itr, "/")) {
            token_itr++;
            Node *expr_node = new Node(NodeKind::DIV);
            expr_node->args.push_back(node);
            expr_node->args.push_back(unary(token_itr));
            node = expr_node;
        } else if (isReserved(token_itr, "%")) {
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
    if (isReserved(token_itr, "+")) {
        token_itr++;
        return primary(token_itr);
    } else if (isReserved(token_itr, "-")) {
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
    if (isReserved(token_itr, "(")) {
        token_itr++;
        Node *node = expr(token_itr);
        if (!isReserved(token_itr, ")")) {
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
        node->offset = (token_itr->txt.at(0) - 'a' + 1) * 8;
        token_itr++;
        return node;
    } else {
        Error::at(token_itr->pos, "'('または数字，識別子ではありません");
        return nullptr;
    }
}
