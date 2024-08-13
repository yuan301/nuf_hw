#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 計算最小合併成本的函數
int minCostToAddNumbers(vector<int>& numbers) {
    // 創建最小堆（優先隊列）
    priority_queue<int, vector<int>, greater<int>> minHeap(numbers.begin(), numbers.end());

    int totalCost = 0;

    // 當堆中有多於一個數字時，繼續合併
    while (minHeap.size() > 1) {
        // 取出兩個最小的數字
        int first = minHeap.top();
        minHeap.pop();
        int second = minHeap.top();
        minHeap.pop();

        // 計算合併這兩個數字的成本
        int cost = first + second;
        totalCost += cost;

        // 將結果插入堆中
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