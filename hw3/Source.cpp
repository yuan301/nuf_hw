#include <iostream>
#include <cmath>
#include <limits>

class Node {
public:
    int coef;   // 係數
    int exp;    // 指數
    Node* link;  // 下一個節點的指標
};

class Polynomial {
private:
    Node* header;       // 多項式的鏈表頭節點
    static Node* av;    // 可用節點的鏈表頭節點

public:
    // 建構子
    Polynomial();
    // 解構子
    ~Polynomial();

    // 輸入運算子
    friend std::istream& operator>>(std::istream& is, Polynomial& x);
    // 輸出運算子
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& x);

    // 複製建構子
    Polynomial(const Polynomial& a);
    // 賦值運算子
    const Polynomial& operator=(const Polynomial& a);

    // 多項式相加
    Polynomial operator+(const Polynomial& b) const;
    // 多項式相減
    Polynomial operator-(const Polynomial& b) const;
    // 多項式相乘
    Polynomial operator*(const Polynomial& b) const;

    // 多項式評估
    float Evaluate(float x) const;
};

// 初始化可用節點的鏈表頭節點
Node* Polynomial::av = nullptr;

// 多項式的建構子
Polynomial::Polynomial() {
    header = new Node;
    header->link = header;
}

// 輸入多項式的運算子
std::istream& operator>>(std::istream& is, Polynomial& x) {
    int n;
    is >> n;             // 多項式項數
    Node* current = x.header;

    for (int i = 0; i < n; ++i) {
        Node* newNode = new Node;
        is >> newNode->coef >> newNode->exp;
        newNode->link = nullptr;

        current->link = newNode;
        current = newNode;
    }

    // 將最後一個節點的 link 指向頭節點，形成循環鏈表
    current->link = x.header;

    return is;
}

// 輸出多項式的運算子
std::ostream& operator<<(std::ostream& os, const Polynomial& x) {
    Node* current = x.header->link; // 跳過頭節點
    int count = 0;

    while (current != x.header) {
        os << (count > 0 ? " + " : "") << current->coef;

        if (current->exp > 0) {
            os << "x";
            if (current->exp > 1)
                os << "^" << current->exp;
        }

        current = current->link;
        ++count;
    }

    return os;
}

// 多項式複製建構子的實作
Polynomial::Polynomial(const Polynomial& a) {
    Node* current_a = a.header->link; // 跳過 a 的頭節點
    header = new Node;  // 初始化新的頭節點
    Node* current_this = header;

    while (current_a != a.header) {
        Node* newNode = new Node;
        newNode->coef = current_a->coef;
        newNode->exp = current_a->exp;
        newNode->link = nullptr;

        current_this->link = newNode;
        current_this = newNode;
        current_a = current_a->link;
    }

    // 將最後一個節點的 link 指向頭節點，形成循環鏈表
    current_this->link = header;
}

// 賦值運算子的實作
const Polynomial& Polynomial::operator=(const Polynomial& a) {
    if (this != &a) {
        // 清除原有節點
        Node* current = header->link; // 跳過頭節點
        while (current != header) {
            Node* temp = current;
            current = current->link;
            delete temp;
        }

        // 複製新的多項式
        Node* current_a = a.header->link; // 跳過 a 的頭節點
        Node* current_this = header;

        while (current_a != a.header) {
            Node* newNode = new Node;
            newNode->coef = current_a->coef;
            newNode->exp = current_a->exp;
            newNode->link = nullptr;

            current_this->link = newNode;
            current_this = newNode;
            current_a = current_a->link;
        }

        // 將最後一個節點的 link 指向頭節點，形成循環鏈表
        current_this->link = header;
    }

    return *this;
}


// 解構子的實作
Polynomial::~Polynomial() {
    Node* current = header->link; // 跳過頭節點
    while (current != header) {
        Node* temp = current;
        current = current->link;
        delete temp;
    }

    // 釋放頭節點
    delete header;
}

// 多項式相加的實作
Polynomial Polynomial::operator+(const Polynomial& b) const {
    Polynomial result;

    Node* current_a = header->link; // 跳過頭節點
    Node* current_b = b.header->link; // 跳過b的頭節點
    Node* current_result = result.header;

    while (current_a != header || current_b != b.header) {
        Node* newNode = new Node;

        if (current_a->exp == current_b->exp) {
            newNode->coef = current_a->coef + current_b->coef;
            newNode->exp = current_a->exp;
            current_a = current_a->link;
            current_b = current_b->link;
        }
        else if (current_a->exp > current_b->exp) {
            newNode->coef = current_a->coef;
            newNode->exp = current_a->exp;
            current_a = current_a->link;
        }
        else {
            newNode->coef = current_b->coef;
            newNode->exp = current_b->exp;
            current_b = current_b->link;
        }

        newNode->link = nullptr;
        current_result->link = newNode;
        current_result = newNode;
    }

    // 將最後一個節點的 link 指向頭節點，形成循環鏈表
    current_result->link = result.header;

    return result;
}

// 多項式相減的實作
Polynomial Polynomial::operator-(const Polynomial& b) const {
    Polynomial result;

    Node* current_a = header->link; // 跳過頭節點
    Node* current_b = b.header->link; // 跳過b的頭節點
    Node* current_result = result.header;

    while (current_a != header || current_b != b.header) {
        Node* newNode = new Node;

        if (current_a->exp == current_b->exp) {
            newNode->coef = current_a->coef - current_b->coef;
            newNode->exp = current_a->exp;
            current_a = current_a->link;
            current_b = current_b->link;
        }
        else if (current_a->exp > current_b->exp) {
            newNode->coef = current_a->coef;
            newNode->exp = current_a->exp;
            current_a = current_a->link;
        }
        else {
            newNode->coef = -current_b->coef;
            newNode->exp = current_b->exp;
            current_b = current_b->link;
        }

        newNode->link = nullptr;
        current_result->link = newNode;
        current_result = newNode;
    }

    // 將最後一個節點的 link 指向頭節點，形成循環鏈表
    current_result->link = result.header;

    return result;
}

// 多項式相乘的實作
Polynomial Polynomial::operator*(const Polynomial& b) const {
    Polynomial result;

    Node* current_a = header->link; // 跳過頭節點
    Node* current_result = result.header;

    while (current_a != header) {
        Node* current_b = b.header->link; // 跳過b的頭節點

        while (current_b != b.header) {
            Node* newNode = new Node;
            newNode->coef = current_a->coef * current_b->coef;
            newNode->exp = current_a->exp + current_b->exp;
            newNode->link = nullptr;

            // 將新節點插入結果多項式
            Node* temp = current_result->link;
            Node* prev = current_result;

            while (temp != result.header && temp->exp > newNode->exp) {
                prev = temp;
                temp = temp->link;
            }

            if (temp != result.header && temp->exp == newNode->exp) {
                // 同次幂的項相加
                temp->coef += newNode->coef;
                delete newNode;
            }
            else {
                // 插入新節點
                prev->link = newNode;
                newNode->link = temp;
                current_result = newNode;  // 修正此行
            }

            current_b = current_b->link;
        }

        current_a = current_a->link;
    }

    // 將最後一個節點的 link 指向頭節點，形成循環鏈表
    current_result->link = result.header;

    return result;
}


// 多項式評估的實作
float Polynomial::Evaluate(float x) const {
    float result = 0.0;
    Node* current = header->link; // 跳過頭節點

    while (current != header) {
        result += current->coef * std::pow(x, current->exp);
        current = current->link;
    }

    return result;
}

int main() {
    Polynomial p1, p2, p3;

    std::cout << "輸入第一個多項式:\n";
    std::cin >> p1;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "輸入第二個多項式:\n";
    std::cin >> p2;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    p3 = p1 * p2;
    std::cout << "兩多項式相乘的結果: " << p3 << std::endl;

    return 0;
}
