#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

inline long long Pow(long long x, long long y) {
    long long res = 1;
    for (long long i = 0; i < y; i++)
        res *= x;
    return res;
}

enum Token_Type {
    TK_LBR,     // 左括号
    TK_RBR,     // 右括号
    TK_POW,     // 乘方
    TK_MUL,     // 乘积
    TK_DIV,     // 除法
    TK_PLS,     // 加法
    TK_MIN,     // 减法
    TK_INT,     // 整数
    TK_NEG      // 负数
};

typedef struct Token {
    Token_Type type;
    char val[32];
    bool is_neg;
} Token;

Token tokens[10000] = {};
int tokens_size = 0;

bool check_parentheses(int p, int q) {
    if (p > q)
        return false;
    if (tokens[p].type == TK_LBR && tokens[q].type == TK_RBR) {
        int depth = 0;
        for (int i = p; i <= q; i++) {
            if (tokens[i].type == TK_LBR) {
                depth++;
            } else if (tokens[i].type == TK_RBR) {
                depth--;
            }
            if (depth <= 0 && i != q) {
                return false;
            }
        }
        return true;
    }
    return false;
}

static int find_main_operand(int p, int q) {
    int op = p;
    int priority = 5;
    int depth = 0;
    for (int i = p; i <= q; i++) {
        if (tokens[i].type == TK_LBR) {
            depth++;
        } else if (tokens[i].type == TK_RBR) {
            depth--;
        }
        if (depth < 0) {
            return false; // bad expression
        }
        bool is_operand = tokens[i].type == TK_PLS || tokens[i].type == TK_MIN ||
                          tokens[i].type == TK_MUL || tokens[i].type == TK_DIV || 
                          tokens[i].type == TK_POW || tokens[i].type == TK_NEG;
        if (is_operand && depth == 0) {
            int cur_prior = 0;
            switch (tokens[i].type) {
                case TK_PLS: case TK_MIN: cur_prior = 1;    break;
                case TK_MUL: case TK_DIV: cur_prior = 2;    break;
                case TK_POW: cur_prior = 3; break;
                case TK_NEG: cur_prior = 4; break;
                default: break;
            }
            if (cur_prior <= priority) {
                op = i;
                priority = cur_prior;
            }
        }
    }
    if (depth != 0)
        return -1;  // 括号不匹配
    return op;
}

static long long eval(int p, int q, bool *success) {
    if (p == q) {
        long long num;
        sscanf(tokens[p].val, "%lld", &num);
        return num;
    }
    else if (check_parentheses(p, q) == true) {
        return eval(p + 1, q - 1, success);
    }
    else {
        int op = find_main_operand(p, q);

        if (tokens[op].type == TK_NEG) {    // 处理负号
            // 统计连续的 '~' 运算符数量
            int neg_count = 1;
            int current_op = op;
            while (current_op > p && tokens[current_op - 1].type == TK_NEG) {
                neg_count++;
                current_op--;
            }
            long long val = eval(op + 1, q, success);
            if (!*success) return 0;
            if (neg_count % 2 == 0)
                return val;
            else
                return -val;
        }

        long long val1 = eval(p, op - 1, success); // 主运算符左边的值
        long long val2 = eval(op + 1, q, success); // 主运算符右边的值

        switch (tokens[op].type) {
            case TK_PLS: return val1 + val2;
            case TK_MIN: return val1 - val2;
            case TK_MUL: return val1 * val2;
            case TK_DIV: return val1 / val2;
            case TK_POW: return Pow(val1, val2);
            default: *success = false; return 0;
        }
    }
}

int main() {
    string str;
    cin >> str;
    string temp = "";
    bool prev_is_num = false;
    auto check = [&]() {
        if (prev_is_num) {
            tokens[tokens_size].type = TK_INT;
            strncpy(tokens[tokens_size++].val, temp.c_str(), temp.size());
            temp = "";
            prev_is_num = false;
        }
    };
    for (const auto& ch : str) {
        switch (ch) {
            case '+': check();  tokens[tokens_size++].type = TK_PLS;  break;
            case '-': check();  tokens[tokens_size++].type = TK_MIN;  break;
            case '*': check();  tokens[tokens_size++].type = TK_MUL;  break;
            case '/': check();  tokens[tokens_size++].type = TK_DIV;  break;
            case '~': check();  tokens[tokens_size++].type = TK_NEG;  break;
            case '^': check();  tokens[tokens_size++].type = TK_POW;  break;
            case '(': check();  tokens[tokens_size++].type = TK_LBR;  break;
            case ')': check();  tokens[tokens_size++].type = TK_RBR;  break;
            default:  break;
        }
        if (ch >= '0' && ch <= '9') {
            temp += ch;
            prev_is_num = true;
        }
    }
    check();
    bool success = true;
    long long res = eval(0, tokens_size - 1, &success);
    cout << res;
    return 0;
}