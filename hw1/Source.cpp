#include <iostream>
#include <vector>

using namespace std;

// 計算集合 S 的冪集
void computePowerset(const vector<char>& S, vector<char>& currentSubset, int index, vector<vector<char>>& powerset) {
	// 如果已處理完 S 中所有元素，把當前子集加入冪集
	if (index == S.size()) {

		powerset.push_back(currentSubset); return;
	}

	// 處理包含當前元素的情況
	currentSubset.push_back(S[index]);
	computePowerset(S, currentSubset, index + 1, powerset);

	// 處理不包含當前元素的情況
	currentSubset.pop_back();
	computePowerset(S, currentSubset, index + 1, powerset);
}

int main() {
	vector<char> S; int n;

	cout << "請輸入集合的元素個數 n: "; cin >> n;

	cout << "請依次輸入集合的元素: "; for (int i = 0; i < n; ++i) {
		char element; cin >> element;
		S.push_back(element);
	}

	vector<vector<char>> powerset; vector<char> currentSubset;

	// 初始化一個空子集，然後計算冪集
	computePowerset(S, currentSubset, 0, powerset);

	cout << "冪集 (Powerset)：" << endl;
	for (const vector<char>& subset : powerset) {
		cout << "{";
		for (char element : subset) {
			std::cout << element << " ";
		}
		cout << "}" << endl;
	}

	return 0;
}
