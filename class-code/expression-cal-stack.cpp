#include <deque>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>

std::map<char, int> symbolTable = {std::pair<char, int>('(', 3),
                                   std::pair<char, int>(')', 3),
                                   std::pair<char, int>('*', 2),
                                   std::pair<char, int>('/', 2),
                                   std::pair<char, int>('+', 1),
                                   std::pair<char, int>('-', 1),
                                    std::pair<char, int>(';', 0)};

template<typename T>
T parse(std::string number) {
    std::istringstream ss(number);
    T res;
    ss >> res;
    return res;
}

bool is_exist(std::deque<char>& deque, char target) {
    for (const auto& elm : deque) {
        if (elm == target) {
            return true;
        }
    }
    return false;
}

int main() {
    std::string expression;
    std::cin >> expression;

    std::string curNumber = "";
    std::deque<char> symbolStack;
    std::vector<std::string> polandExpression;

    for (const auto& ch : expression) {
        if (ch != '+' && ch != '-' &&
            ch != '*' && ch != '/' &&
            ch != '(' && ch != ')') {
            curNumber += ch;
        } else {
            polandExpression.push_back(curNumber);
            curNumber = "";
            char st = symbolStack.empty() ? ';' : symbolStack.front();    // 栈顶符号
            if (ch == ')') {
                while (st != '(') {
                    polandExpression.push_back(std::string(&st));
                    symbolStack.pop_front();
                    st = symbolStack.front();
                }
                symbolStack.pop_front();
            } else {
                if (symbolTable[ch] <= symbolTable[st] &&
                    !is_exist(symbolStack, '(')) {
                    while (symbolTable[ch] <= symbolTable[st]) {
                        std::string s;
                        s = st;
                        polandExpression.push_back(s);
                        symbolStack.pop_front();
                        st = symbolStack.front();
                    }
                }
                symbolStack.push_front(ch);
            }
        }
    }

    while (!symbolStack.empty()) {
        polandExpression.push_back(&symbolStack.front());
        symbolStack.pop_front();
    }

    for (const auto& elm : polandExpression) {
        std::cout << elm << " ";
    }

    return 0;
}