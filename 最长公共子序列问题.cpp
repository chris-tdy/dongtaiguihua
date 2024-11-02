#include <iostream>
#include <vector>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

// 动态规划求解最长公共子序列
string longestCommonSubsequence(const string& X, const string& Y) {
    int m = X.size();
    int n = Y.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // 构建dp数组
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // 回溯得到LCS字符串
    string lcs;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs = X[i - 1] + lcs; // 添加到LCS字符串前面
            --i;
            --j;
        }
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            --i;
        }
        else {
            --j;
        }
    }

    return lcs;
}

void testLCS(const string& X, const string& Y) {
    // 记录开始时间
    auto start = high_resolution_clock::now();

    string result = longestCommonSubsequence(X, Y);

    // 记录结束时间
    auto stop = high_resolution_clock::now();

    // 计算耗时
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "字符串X: " << X << "\n字符串Y: " << Y << endl;
    cout << "最长公共子序列是: " << result << endl;
    cout << "计算时间: " << duration.count() << " 微秒" << endl;
    cout << "----------------------------------------" << endl;
}

int main() {
    // 测试用例1
    testLCS("ABCBDAB", "BDCAB");

    // 测试用例2
    testLCS("AGGTAB", "GXTXAYB");

    // 测试用例3
    testLCS("XMJYAUZ", "MZJAWXU");

    return 0;
}