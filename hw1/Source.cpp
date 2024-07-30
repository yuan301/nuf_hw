#include <iostream>
#include <vector>

using namespace std;

// �p�ⶰ�X S ������
void computePowerset(const vector<char>& S, vector<char>& currentSubset, int index, vector<vector<char>>& powerset) {
	// �p�G�w�B�z�� S ���Ҧ������A���e�l���[�J����
	if (index == S.size()) {

		powerset.push_back(currentSubset); return;
	}

	// �B�z�]�t��e���������p
	currentSubset.push_back(S[index]);
	computePowerset(S, currentSubset, index + 1, powerset);

	// �B�z���]�t��e���������p
	currentSubset.pop_back();
	computePowerset(S, currentSubset, index + 1, powerset);
}

int main() {
	vector<char> S; int n;

	cout << "�п�J���X�������Ӽ� n: "; cin >> n;

	cout << "�Ш̦���J���X������: "; for (int i = 0; i < n; ++i) {
		char element; cin >> element;
		S.push_back(element);
	}

	vector<vector<char>> powerset; vector<char> currentSubset;

	// ��l�Ƥ@�ӪŤl���A�M��p�⾭��
	computePowerset(S, currentSubset, 0, powerset);

	cout << "���� (Powerset)�G" << endl;
	for (const vector<char>& subset : powerset) {
		cout << "{";
		for (char element : subset) {
			std::cout << element << " ";
		}
		cout << "}" << endl;
	}

	return 0;
}
