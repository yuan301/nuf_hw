#include <iostream>
#include <math.h>
#include <chrono>
using namespace std;
class Term {
    friend class Polynomial;
    friend ostream& operator<<(ostream& os, const Polynomial& p);
    friend istream& operator>>(istream& os, const Polynomial& p);
private:
    float coef; // 係數
    int exp;    // 次方項

public:
    float GetCoef() const { return coef; }
    int GetExp() const { return exp; }
};
class Polynomial {
    friend ostream& operator<<(ostream& os, const Polynomial& p);
    friend istream& operator>>(istream& os, const Polynomial& p);
private:
    Term* termArray;
    int capacity; // 空間大小
    int terms;    // 非零項數量

public:
    Polynomial(); // 建構子
    Polynomial(const Polynomial& poly); // 複製建構子
    ~Polynomial(); // 解構子
    Polynomial Add(const Polynomial& poly);
    Polynomial Mult(const Polynomial& poly);
    float Eval(float f);
    void NewTerm(const float newCoef, const int newExp); // 新增非零項
};

Polynomial::Polynomial() : capacity(2), terms(0) {
    termArray = new Term[capacity];
}

Polynomial::Polynomial(const Polynomial& poly) {
    capacity = poly.capacity;
    terms = poly.terms;
    termArray = new Term[capacity];
    for (int i = 0; i < terms; ++i) {
        termArray[i] = poly.termArray[i];
    }
}

Polynomial::~Polynomial() {
    //刪除不需要的陣列
    delete[] termArray;
}

void Polynomial::NewTerm(const float newCoef, const int newExp) {
    // 空間不足時重新配置空間
    if (capacity == terms) {
        int newCapacity = capacity * 2;
        Term* tempArray = new Term[newCapacity];
        for (int i = 0; i < capacity; ++i) {
            tempArray[i] = termArray[i];
        }
        delete[] termArray;
        termArray = tempArray;
        capacity = newCapacity;
    }
    termArray[terms].coef = newCoef;
    termArray[terms].exp = newExp;
    terms++;
}

Polynomial Polynomial::Add(const Polynomial& poly) {
    Polynomial result;
    int i = 0, j = 0;
    while (i < terms && j < poly.terms) {
        if (termArray[i].exp == poly.termArray[j].exp) {
            result.NewTerm(termArray[i].coef + poly.termArray[j].coef, termArray[i].exp);
            i++;
            j++;
        }
        else if (termArray[i].exp > poly.termArray[j].exp) {
            result.NewTerm(termArray[i].coef, termArray[i].exp);
            i++;
        }
        else {
            result.NewTerm(poly.termArray[j].coef, poly.termArray[j].exp);
            j++;
        }
    }
    while (i < terms) {
        result.NewTerm(termArray[i].coef, termArray[i].exp);
        i++;
    }
    while (j < poly.terms) {
        result.NewTerm(poly.termArray[j].coef, poly.termArray[j].exp);
        j++;
    }
    return result;
}

Polynomial Polynomial::Mult(const Polynomial& poly) {
    Polynomial result;
    for (int i = 0; i < terms; ++i) {
        for (int j = 0; j < poly.terms; ++j) {
            int newExp = termArray[i].exp + poly.termArray[j].exp;
            float newCoef = termArray[i].coef * poly.termArray[j].coef;
            result.NewTerm(newCoef, newExp);
        }
    }
    return result;
}

float Polynomial::Eval(float f) {
    float x = 0;
    for (int i = 0; i < terms; i++) {
        x += termArray[i].coef * pow(f, termArray[i].exp);
    }
    return x;
}

ostream& operator<<(ostream& os, const Polynomial& p) {
    for (int i = 0; i < p.terms; ++i) {
        if (p.termArray[i].GetExp() == 0) {
            os << p.termArray[i].GetCoef();
        }
        else {
            os << p.termArray[i].GetCoef() << "X^" << p.termArray[i].GetExp();
        }
        if (i != p.terms - 1) {
            os << " + ";
        }
    }
    return os;
}
istream& operator>>(istream& is, Polynomial& p) {
    int terms;
    float coef, exp;

    is >> terms;
    while (cin >> coef >> exp) {
        if (coef == -1 && exp == -1) {
            break; // 結束輸入
        }
        p.NewTerm(coef, terms);
    }
    return is;
}

int main() {
    Polynomial poly1, poly2;

    // 多項式1的輸入
    cout << "輸入多項式1(係數、次方項) :  " << endl;
    cin >> poly1;
    // 多項式2的輸入
    cout << "輸入多項式2(係數、次方項) : " << endl;
    cin >> poly2;
    //計算X代入後多項式的值
    float value;
    cout << "輸出X : ";
    cin >> value;
    // 開始計時
    auto start = chrono::high_resolution_clock::now();
    //輸出多項式
    cout << "多項式 1: " << poly1 << endl;
    cout << "多項式 2: " << poly2 << endl;

    // 計算Add和Mult
    Polynomial additionResult = poly1.Add(poly2);
    Polynomial multiplicationResult = poly1.Mult(poly2);

    // 輸出Add和Mult的計算結果
    cout << "Add : " << additionResult << endl;
    cout << "Mult : " << multiplicationResult << endl;

    

    cout << "Eval 1 = " << value << ": " << poly1.Eval(value) << endl;
    cout << "Eval 2 = " << value << ": " << poly2.Eval(value) << endl;
    // 結束計時
    auto end = chrono::high_resolution_clock::now();

    // 計算時間差
    chrono::duration<double> elapsed = end - start;
    cout << "運算執行時間: " << elapsed.count() << " seconds" << endl;
    return 0;
}