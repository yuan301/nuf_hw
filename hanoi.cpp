#include <iostream>
using namespace std;

int moved = 0;

void hanoi(int n, char A, char B, char C) {
	if (n == 1) {
		cout << "Move " << A << " " << C << endl;
		moved++;
	}
	else {
		hanoi(n - 1, A, B, C);
		hanoi(1, A, C, B);
		hanoi(n - 1, B, C, A);
	}
}

int main() {
	int n;
	cin >> n;
	hanoi(n,'A', 'B', 'C');
	cout << "moved = " << moved << endl;
	return 0;
}