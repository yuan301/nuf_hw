#include <iostream>
#include <stack>
#include <string>

using namespace std;

// 檢查字串中的括號是否正確配對
bool isBalanced(const string& str) {
    stack<char> stk;
    for (char ch : str) {
        switch (ch) {
        case '(': // 遇到開括號，推入堆疊
        case '[':
        case '{':
            stk.push(ch);
            break;
        case ')': // 遇到閉括號，檢查堆疊
            if (stk.empty() || stk.top() != '(') {
                return false;
            }
            stk.pop();
            break;
        case ']':
            if (stk.empty() || stk.top() != '[') {
                return false;
            }
            stk.pop();
            break;
        case '}':
            if (stk.empty() || stk.top() != '{') {
                return false;
            }
            stk.pop();
            break;
        }
    }
    // 檢查堆疊是否為空
    return stk.empty();
}

int main() {
    int T;
    cin >> T;
    cin.ignore(); // 忽略換行符，準備讀取字串

    while (T--) {
        string str;
        getline(cin, str); // 讀取每一筆字串

        if (isBalanced(str)) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
    return 0;
}