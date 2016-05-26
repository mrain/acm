#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    long long a, b, c;
    cin >> a >> b >> c;
    long long gap = b - a;
    if (gap == 0 || (gap * c > 0 && gap % c == 0))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}
