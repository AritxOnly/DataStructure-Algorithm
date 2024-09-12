#include <iostream>
#include <string>

using namespace std;

int main() {
    string str;
    cin >> str;
    string newStr = "";
    bool bar = false;
    char prevChar = (str.empty()) ? '-' :str[0];
    for (const auto& ch : str) {
        if (ch == '-') {
            bar = true;
            continue;
        }
        if (bar) {
            if (static_cast<int>(prevChar) <= static_cast<int>(ch)) {
                for (char i = prevChar + 1; i < ch; i++) {
                    newStr += i;
                }
            } else {
                for (char i = prevChar - 1; i > ch; i--) {
                    newStr += i;
                }
            }
            bar = false;
        }
        newStr += ch;
        prevChar = ch;
    }
    cout << newStr << endl;
    return 0;
}