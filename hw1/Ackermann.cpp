#include <iostream> 
using namespace std;
int ackermann(int m, int n) {
	// 當 m 為 0 時，返回 n + 1 
	if (m == 0) {
	return n + 1;
	}
// 當 m 大於 0 且 n 為 0 時，調用Ackermann函數，m 減 1，n 為 1 
	if (n == 0) {
		return ackermann(m - 1, 1);
	}
// 計算 A(m-1, A(m, n-1))
	return ackermann(m - 1, ackermann(m, n - 1));
}

int main() {
	int m, n;
	cout << "請輸入 m 和 n 的值: ";
	cin >> m >> n;

	int result = ackermann(m, n);
	cout << "Ackermann(" << m << ", " << n << ") = " << result << endl;

	return 0;
}

