#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

int n, a, b, c, d, a1, a2, a3, a4;

int main() {
    cin >> n >> a >> b >> c >> d;
    a1 = a + b;
    a2 = a + c;
    a3 = d + b;
    a4 = d + c;
    int j = max(max(a1, a2), max(a3, a4));
    int k = min(min(a1, a2), min(a3, a4));
    long long ans = max((long long)n - (j - k), 0ll) * n;
    cout << ans << endl;
    return 0;
}
