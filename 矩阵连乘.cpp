#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// ��̬�滮���������˷�����
void MatrixChainOrder(vector<int>& p, vector<vector<int>>& m, vector<vector<int>>& s) {
    int n = p.size() - 1; // �������
    for (int i = 1; i <= n; ++i) {
        m[i][i] = 0; // ��������ĳ˷�����Ϊ0
    }

    // l �����ĳ���
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

// ��ӡ�������Ż�����
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
    // ��������ά������
    vector<int> p = { 30, 35, 15, 5, 10, 20, 25 };
    int n = p.size() - 1;

    // ��ʼ����ά����洢��С���ۺͷָ��
    vector<vector<int>> m(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> s(n + 1, vector<int>(n + 1, 0));

    // ��¼��ʼʱ��
    auto start = high_resolution_clock::now();

    // ���ú�������������˷�����
    MatrixChainOrder(p, m, s);

    // ��¼����ʱ��
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    // ������
    cout << "Minimum number of multiplications is " << m[1][n] << endl;
    cout << "Optimal parenthesization is: ";
    PrintOptimalParens(s, 1, n);
    cout << endl;

    // �������ʱ��
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

    return 0;
}