#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// �p��̤p�X�֦��������
int minCostToAddNumbers(vector<int>& numbers) {
    // �Ыس̤p��]�u�����C�^
    priority_queue<int, vector<int>, greater<int>> minHeap(numbers.begin(), numbers.end());

    int totalCost = 0;

    // ��襤���h��@�ӼƦr�ɡA�~��X��
    while (minHeap.size() > 1) {
        // ���X��ӳ̤p���Ʀr
        int first = minHeap.top();
        minHeap.pop();
        int second = minHeap.top();
        minHeap.pop();

        // �p��X�ֳo��ӼƦr������
        int cost = first + second;
        totalCost += cost;

        // �N���G���J�襤
        minHeap.push(cost);
    }

    return totalCost;
}

int main() {
    int n;
    while (cin >> n) {
        if (n == 0) break;
        vector<int> numbers(n);
        for (int i = 0; i < n; ++i) {
            cin >> numbers[i];
        }

        int result = minCostToAddNumbers(numbers);
        cout << result << endl;
    }
    return 0;
}