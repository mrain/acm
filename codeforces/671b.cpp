#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

int n, k, a[500010];
long long sum;

int main() {
    sum = 0;
    cin >> n >> k;
    for (int i = 0; i < n; ++ i) {
        cin >> a[i];
        sum += a[i];
    }
    sort(a, a + n);
    long long sumh = 0, sumt = 0;
    int j = 0, ah = -1, at = -1;
    for (int i = n - 1; i >= 0; -- i) {
        if (i < n - 1 || a[i] != a[i + 1]) {
            long long day = sumt - ((long long)n - i - 1) * a[i];
            if (day == k) {
                at = a[i];
                break;
            } else if (day > k) {
                int l = a[i], r = a[i + 1], mid = (l + r) >> 1;
                while (r - l > 1) {
                    day = sumt - ((long long)n - i - 1) * mid;
                    if (day > k) l = mid;
                    else r = mid;
                    mid = (l + r) >> 1;
                }
                at = r;
                break;
            }
        }
        sumt += a[i];
    }
    for (int j = 0; j < n; ++ j) {
        if (j == 0 || a[j] != a[j - 1]) {
            long long day = (long long)j * a[j] - sumh;
            if (day == k) {
                ah = a[j];
                break;
            } else if (day > k) {
                int l = a[j - 1], r = a[j], mid = (l + r) >> 1;
                while (r - l > 1) {
                    day = (long long)j * mid - sumh;
                    if (day <= k) l = mid;
                    else r = mid;
                    mid = (l + r) >> 1;
                }
                ah = l;
                break;
            }
        }
        sumh += a[j];
    }
    //cout << at << ' ' << ah << endl;
    if (at == -1 || ah == -1 || at <= ah) cout << (sum % n == 0 ? 0 : 1) << endl;
    else cout << at - ah << endl;
    return 0;
}
