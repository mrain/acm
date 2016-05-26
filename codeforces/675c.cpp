#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <map>
using namespace std;

int n, a[100010], cnt[100010];
map <long long, int> nearest;

int main() {
    cin >> n;
    nearest.clear();
    memset(cnt, 0, sizeof(cnt));
    long long cur = 0;
    int ans = 0;
    for (int i = 0; i < n; ++ i) {
        cin >> a[i];
        cur += a[i];
        if (nearest.count(cur) != 0) {
            int k = nearest[cur];
            cnt[i] = cnt[k] + 1;
            ans = max(ans, cnt[i]);
        }
        nearest[cur] = i;
    }
    cout << n - ans - 1 << endl;
    return 0;
}
