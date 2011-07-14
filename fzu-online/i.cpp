#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int tests, caseno;
string str, f[110][110], g[110][110];
string inf;
int n, k;

string rev(const string &a) {
    string b = a;
    reverse(b.begin(), b.end());
    return b;
}

int main() {
    freopen("input.txt", "r", stdin);
    for (int i = 0; i < 102; ++ i) inf += 'Z';
    cin >> tests;
    while (tests --) {
        cin >> n >> k >> str;
        for (int i = 0; i <= n; ++ i) {
            f[i][0] = str.substr(0, i + 1);
            g[i][0] = rev(f[i][0]);
            for (int j = 1; j <= k; ++ j)
                f[i][j] = g[i][j] = inf;
        }
        for (int i = 1; i < n; ++ i)
            for (int j = 1; j <= k; ++ j) {
                f[i][j] = min(f[i - 1][j] + str[i], str[i] + g[i - 1][j - 1]);
                g[i][j] = min(str[i] + g[i - 1][j], f[i - 1][j - 1] + str[i]);
            }
        string ans = inf;
        for (int i = 0; i <= k; ++ i)
            ans = min(f[n - 1][i], ans);
        cout << "Case "<< ++ caseno << ": " << ans << endl;
    }
}

