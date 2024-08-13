#include <iostream>
#include <stack>
#include <string>

using namespace std;

// �ˬd�r�ꤤ���A���O�_���T�t��
bool isBalanced(const string& str) {
    stack<char> stk;
    for (char ch : str) {
        switch (ch) {
        case '(': // �J��}�A���A���J���|
        case '[':
        case '{':
            stk.push(ch);
            break;
        case ')': // �J�쳬�A���A�ˬd���|
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
    // �ˬd���|�O�_����
    return stk.empty();
}

int main() {
    int T;
    cin >> T;
    cin.ignore(); // ��������šA�ǳ�Ū���r��

    while (T--) {
        string str;
        getline(cin, str); // Ū���C�@���r��

        if (isBalanced(str)) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
    return 0;
}