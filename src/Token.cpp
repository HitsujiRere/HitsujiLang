#include "Token.hpp"
#include "Error.hpp"

bool is_ident_char(char ch) {
    return ('a' <= ch && ch <= 'z')
        || ('A' <= ch && ch <= 'Z')
        || ('0' <= ch && ch <= '9')
        || (ch == '_');
}

bool is_ident_head_char(char ch) {
    return ('a' <= ch && ch <= 'z')
        || ('A' <= ch && ch <= 'Z')
        || (ch == '_');
}

size_t search_reserves(const std::string& txt, size_t i) {
    for (const auto& reserve : reserves) {
        if (reserve == txt.substr(i, reserve.size())) {
            return reserve.size();
        }
    }
    for (const auto& reserve : reserves_ident) {
        if (reserve == txt.substr(i, reserve.size()) && !is_ident_char(txt.at(i + reserve.size() + 1))) {
            return reserve.size();
        }
    }
    return 0;
}

size_t get_number_len(const std::string& txt, size_t i) {
    size_t len = 0;
    for (; '0' <= txt.at(i + len) && txt.at(i + len) <= '9'; len++) { }
    return len;
}

int parseToInt(const std::string& txt, size_t i) {
    int num = 0;
    for (size_t j = 0; '0' <= txt.at(i + j) && txt.at(i + j) <= '9'; j++) {
        num = num * 10 + (txt.at(i) - '0');
    }
    return num;
}

std::vector<Token> tokenize(const std::string& code) {
    std::vector<Token> tokens;

    for (size_t i = 0; i < code.size(); i++) {
        if (isspace(code.at(i))) {
            continue;
        }

        // // コメント
        // if (code.substr(i, 2) == "(/") {
        // }

        size_t len = search_reserves(code, i);
        if (len > 0) {
            Token token;
            token.kind = TokenKind::RESERVED;
            token.txt = code.substr(i, len);
            token.pos = i;
            tokens.push_back(token);
            i += len - 1;
            continue;
        }

        // if (is_ident_head_char(*code_itr)) {
        //     size_t len = search_ident(code_itr);
        //     cur = Token::makeNext(TokenKind::IDENT, cur, code_itr - code.begin());
        //     cur->str = substr(code_itr, len);
        //     code_itr += len;
        //     continue;
        // }

        if ('0' <= code.at(i) && code.at(i) <= '9') {
            size_t len = get_number_len(code, i);
            Token token;
            token.kind = TokenKind::NUM;
            token.txt = code.substr(i, len);
            token.pos = i;
            tokens.push_back(token);
            i += len - 1;
            continue;
        }

        Error::at(i, "トークナイズできません");
    }

    return tokens;
}
