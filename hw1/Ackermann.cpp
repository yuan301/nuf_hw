#include <iostream> 
using namespace std;
int ackermann(int m, int n) {
	// �� m �� 0 �ɡA��^ n + 1 
	if (m == 0) {
	return n + 1;
	}
// �� m �j�� 0 �B n �� 0 �ɡA�ե�Ackermann��ơAm �� 1�An �� 1 
	if (n == 0) {
		return ackermann(m - 1, 1);
	}
// �p�� A(m-1, A(m, n-1))
	return ackermann(m - 1, ackermann(m, n - 1));
}

int main() {
	int m, n;
	cout << "�п�J m �M n ����: ";
	cin >> m >> n;

	int result = ackermann(m, n);
	cout << "Ackermann(" << m << ", " << n << ") = " << result << endl;

	return 0;
}

