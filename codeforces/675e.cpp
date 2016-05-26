#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;

int n, a[100010], target[100010];
int f[100010][50], l[100010][50];
long long p[100010];

int log2(int k) {
    int ret = -1;
    while (k) {
        k >>= 1;
        ++ ret;
    }
    return ret;
}

void rmq() {
    for (int i = 0; i < n - 1; ++ i) {
        f[i][0] = a[i];
        l[i][0] = i;
    }

    for (int j = 1; (1 << j) < n - 1; ++ j) {
        int k = 1 << (j - 1);
        for (int i = 0; (i + k + k - 1) < n - 1; ++ i)
            if (f[i][j - 1] > f[i + k][j - 1]) {
                f[i][j] = f[i][j - 1];
                l[i][j] = l[i][j - 1];
            } else {
                f[i][j] = f[i + k][j - 1];
                l[i][j] = l[i + k][j - 1];
            }
    }

    for (int i = 0; i < n - 1; ++ i) {
        if (a[i] == n) continue;
        int len = a[i] - 1 - i;
        //cerr << i << ' ' << a[i] << ' ' << len << endl;
        if (len == 1) target[i] = i + 1;
        else {
            int j = log2(len), k = 1 << j;
            if (f[i + 1][j] > f[i + 1 + len - k][j])
                target[i] = l[i + 1][j];
            else
                target[i] = l[i + 1 + len - k][j];
        }
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n - 1; ++ i)
        cin >> a[i];
    rmq();
    long long ans = 1;
    p[n - 2] = 1;
    for (int i = n - 3; i >= 0; -- i) {
        if (a[i] == n)
            p[i] = n - 1 - i;
        else {
            int j = target[i];
            p[i] = p[j] - a[i] + j - i + n;
        }
        //cerr << i << ' ' << a[i] << ' ' << target[i] << ' ' << p[i] << endl;
        ans += p[i];
    }
    cout << ans << endl;
    return 0;
}
