#include <vector> 
#include <list> 
#include <map> 
#include <set> 
#include <deque> 
#include <queue> 
#include <stack> 
#include <bitset> 
#include <algorithm> 
#include <functional> 
#include <numeric> 
#include <utility> 
#include <complex> 
#include <sstream> 
#include <iostream> 
#include <iomanip> 
#include <cstdio> 
#include <cmath> 
#include <cstdlib> 
#include <cstring> 
#include <ctime> 
#include <cassert> 
using namespace std;

#define x1 _x1
#define y1 _y1
#define x2 _x2
#define y2 _y2

const int maxn = 111111;

int X[maxn], XS;
int Y[maxn], YS;
int cover[maxn * 2];
int leng[maxn * 2];

#define IX(l,r) (((l)+(r))|((l)!=(r)))

vector<pair<int, int> > addE[maxn];
vector<pair<int, int> > delE[maxn];

void update(int l, int r, int ll, int rr, int delta)
{
    if (rr < l || ll > r)
        return;
    int m = l + r >> 1;
    if (ll <= l && rr >= r) {
        cover[IX(l, r)] += delta;
    } else {
        update(l, m, ll, rr, delta);
        update(m+1, r, ll, rr, delta);
    }
    if (cover[IX(l, r)] > 0) {
        leng[IX(l, r)] = Y[r+1] - Y[l];
    } else if (l == r) {
        leng[IX(l, r)] = 0;
    } else {
        leng[IX(l, r)] = leng[IX(l, m)] + leng[IX(m+1, r)];
    }
}

int findIdx(int *a, int n, int v)
{
    return lower_bound(a, a + n, v) - a;
}

long long solve(int n, int lenx, int *x1, int *x2, int leny, int *y1, int *y2, int L)
{
    XS = YS = 0;
    for (int i = 0; i < n; i++) {
        X[XS++] = x1[i];
        X[XS++] = x2[i] + L;
        Y[YS++] = y1[i];
        Y[YS++] = y2[i] + 1;
    }
    X[XS++] = L;
    X[XS++] = lenx + 1;
    sort(X, X + XS), XS = unique(X, X + XS) - X;
    sort(Y, Y + YS), YS = unique(Y, Y + YS) - Y;
    for (int i = 0; i < XS; i++) {
        addE[i].clear();
        delE[i].clear();
    }
    for (int i = 0; i < n; i++) {
        int lx = findIdx(X, XS, x1[i]);
        int rx = findIdx(X, XS, x2[i] + L) - 1;
        int ly = findIdx(Y, YS, y1[i]);
        int ry = findIdx(Y, YS, y2[i] + 1) - 1;
        addE[lx].push_back(make_pair(ly, ry));
        delE[rx].push_back(make_pair(ly, ry));
    }
    memset(cover, 0, sizeof(cover));
    long long ret = 0;
    for (int i = 0; i < XS; i++) {
        for (int j = 0; j < addE[i].size(); j++) {
            update(0, YS - 1, addE[i][j].first, addE[i][j].second, 1);
        }
        if (X[i] >= L && i + 1 < XS && X[i] <= lenx) {
            ret += (long long)(leny - leng[IX(0, YS-1)]) * (X[i+1] - X[i]);
        }
        for (int j = 0; j < delE[i].size(); j++) {
            update(0, YS - 1, delE[i][j].first, delE[i][j].second, -1);
        }
    }
    return ret;
}

int x1[maxn], x2[maxn];
int y1[maxn], y2[maxn];

int main()
{
    int w, h, n, m;
    while (scanf("%d%d%d%d", &w, &h, &n, &m) == 4) {
        for (int i = 0; i < n; i++)
            scanf("%d%d%d%d", x1+i, y1+i, x2+i, y2+i);
        long long ans = solve(n, w, x1, x2, h, y1, y2, m);
        if (m > 1)
            ans += solve(n, h, y1, y2, w, x1, x2, m);
        cout << ans << endl;
    }
}
