#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;

int ax, ay, bx, by, zx, zy;
int n, a1, a2, b1, b2;
double da[100010], db[100010];

double dist(int ax, int ay, int bx, int by) {
    double x = ax - bx, y = ay - by;
    return sqrt(x * x + y * y);
}

int main() {
    cin >> ax >> ay >> bx >> by >> zx >> zy;
    cin >> n;
    double ans = 0;
    for (int i = 0; i < n; ++ i) {
        int x, y;
        cin >> x >> y;
        double dz = dist(x, y, zx, zy);
        da[i] = dist(x, y, ax, ay) - dz;
        db[i] = dist(x, y, bx, by) - dz;
        if (da[i] < da[a1]) {
            a2 = a1; a1 = i;
        } else if (da[i] < da[a2] || a1 == a2) {
            a2 = i;
        }
        if (db[i] < db[b1]) {
            b2 = b1; b1 = i;
        } else if (db[i] < db[b2] || b1 == b2) {
            b2 = i;
        }
        ans += 2 * dz;
    }
    //cerr << a1 << ' ' << a2 << ' ' << b1 << ' ' << b2 << endl;
    //cerr << ans << ' ' << da[a1] << ' ' << da[a2] << ' ' << db[b1] << ' ' << db[b2] << endl;
    if (n == 1) {
        ans += min(da[a1], db[b1]);
    } else {
        if (da[a1] > 0 && db[b1] > 0) {
            ans += min(da[a1], db[b1]);
        } else {
                if (a1 != b1)
                    ans += min(0., da[a1]) + min(0., db[b1]);
                else {
                    ans += min(da[a1] + min(0.0, db[b2]), min(0.0, da[a2]) + db[b1]);
                }
        }
    }
    printf("%.10f\n", ans);
    return 0;
}
