#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// 动态规划求解矩阵链乘法问题
void MatrixChainOrder(vector<int>& p, vector<vector<int>>& m, vector<vector<int>>& s) {
    int n = p.size() - 1; // 矩阵个数
    for (int i = 1; i <= n; ++i) {
        m[i][i] = 0; // 单个矩阵的乘法次数为0
    }

    // l 是链的长度
    for (int l = 2; l <= n; ++l) {
        for (int i = 1; i <= n - l + 1; ++i) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; ++k) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

// 打印最优括号化方案
void PrintOptimalParens(vector<vector<int>>& s, int i, int j) {
    if (i == j) {
        cout << "A" << i;
    }
    else {
        cout << "(";
        PrintOptimalParens(s, i, s[i][j]);
        PrintOptimalParens(s, s[i][j] + 1, j);
        cout << ")";
    }
}

int main() {
    // 矩阵链的维度向量
    vector<int> p = { 30, 35, 15, 5, 10, 20, 25 };
    int n = p.size() - 1;

    // 初始化二维数组存储最小代价和分割点
    vector<vector<int>> m(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> s(n + 1, vector<int>(n + 1, 0));

    // 记录开始时间
    auto start = high_resolution_clock::now();

    // 调用函数解决矩阵链乘法问题
    MatrixChainOrder(p, m, s);

    // 记录结束时间
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    // 输出结果
    cout << "Minimum number of multiplications is " << m[1][n] << endl;
    cout << "Optimal parenthesization is: ";
    PrintOptimalParens(s, 1, n);
    cout << endl;

    // 输出运行时间
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

    return 0;
}