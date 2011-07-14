#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

typedef long long llint;

inline int gcd(int a, int b) {
    if (b == 0) return a;
    if (a == 0) return b;
    int c = a % b;
    for (; c; a = b, b = c, c = a % b);
    return b;
}

struct Point {
    int x, y, z;
    Point() {
        x = y = z = 0;
    }
    Point(int a, int b, int c): x(a), y(b), z(c) {}
    void read() {
        scanf("%d%d%d", &x, &y, &z);
        x += 100001;
        y += 100001;
        z += 100001;
    }
    bool operator <(const Point &p) const{
        if (x == p.x) {
            if (y == p.y) return z < p.z;
            else return y < p.y;
        } else return x < p.x;
    }
    bool operator ==(const Point &p) const{
        return (x == p.x) && (y == p.y) && (z == p.z);
    }
    int small() {
        int d = gcd(gcd(x, y), z);
        x /= d; y /= d; z /= d;
        return d;
    }
    Point operator -(const Point &p) const {
        return Point(x - p.x, y - p.y, z - p.z);
    }
    Point operator *(const int &r) const {
        return Point(x * r, y * r, z * r);
    }
}r[10010], s[10010], dir;

bool check(llint p) { return p > 0; }

struct Event {
    Point p;
    int d, type;
    bool operator <(const Event &e) const {
        if (p == e.p) {
            if (d == e.d) return type < e.type;
            else return d < e.d;
        } else return p < e.p;
    }
    Event() {}
    Event(const Point &q, int t) {
        int l = 0, r = 300001, mid;
        p = q; type = t;
        while (r - l > 1) {
            mid = (l + r) >> 1;
            if (check(p.x - (llint)(mid) * dir.x)
                && check(p.y - (llint)(mid) * dir.y)
                && check(p.z - (llint)(mid) * dir.z))
                l = mid;
            else r = mid - 1;
        }
        if (check(p.x - (llint)(r) * dir.x)
            && check(p.y - (llint)(r) * dir.y)
            && check(p.z - (llint)(r) * dir.z))
            d = r;
        else d = l;
        if (d) p = p - dir * d;
    }
};

vector <Event> list;
int tests, caseno, n, m, ans;

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &tests);
    while (tests --) {
        ans = 0;
        list.clear();
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++ i) s[i].read();
        for (int i = 0; i < m; ++ i) r[i].read();
        dir.read(); dir = dir - Point(100001, 100001, 100001);
        dir.small();
        for (int i = 0; i < n; ++ i) list.push_back(Event(s[i], 1));
        for (int j = 0; j < m; ++ j) list.push_back(Event(r[j], 0));
        sort(list.begin(), list.end());
        for (int i = 0; i < (int)list.size();) {
            int last = i;
            while (last + 1 < (int)list.size() && list[last + 1].p == list[i].p) ++ last;
            int j = i;
            while (j < last && list[j].type != 0) ++ j;
            for (int k = j + 1; k <= last; ++ k)
                if (list[k].type == 1) ++ ans;
            i = last + 1;
        }
        printf("Case %d: %d\n", ++ caseno, ans);
    }
}
