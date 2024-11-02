#include <iostream>
#include <vector>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

// ��̬�滮��������������
string longestCommonSubsequence(const string& X, const string& Y) {
    int m = X.size();
    int n = Y.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // ����dp����
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

    // ���ݵõ�LCS�ַ���
    string lcs;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs = X[i - 1] + lcs; // ��ӵ�LCS�ַ���ǰ��
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
    // ��¼��ʼʱ��
    auto start = high_resolution_clock::now();

    string result = longestCommonSubsequence(X, Y);

    // ��¼����ʱ��
    auto stop = high_resolution_clock::now();

    // �����ʱ
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "�ַ���X: " << X << "\n�ַ���Y: " << Y << endl;
    cout << "�������������: " << result << endl;
    cout << "����ʱ��: " << duration.count() << " ΢��" << endl;
    cout << "----------------------------------------" << endl;
}

int main() {
    // ��������1
    testLCS("ABCBDAB", "BDCAB");

    // ��������2
    testLCS("AGGTAB", "GXTXAYB");

    // ��������3
    testLCS("XMJYAUZ", "MZJAWXU");

    return 0;
}