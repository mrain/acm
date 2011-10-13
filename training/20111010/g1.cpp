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

const int maxn = 16;
const int maxl = 10;

int len[maxn];
int sum[maxn];

char a[maxl][maxl];

int LX, LY, RX, RY;

void lRot(int &x, int &y) 
{
    // (1, 0) -> (0, 1)
    y = -y;
    swap(x, y);
}

void rRot(int &x, int &y)
{
    // (0, 1) -> (1, 0)
    x = -x;
    swap(x, y);
}

void paint(int x, int y, char ch)
{
    if (x >= LX && y >= LY && x <= RX && y <= RY)
        a[x - LX][y - LY] = ch;
}

bool intersect(int L, int R, int a, int b, int c)
{
    int l = min(a, min(b, c));
    int r = max(a, max(b, c));
    return l <= R && L <= r;
}

void go(int d, int x, int y, int dx, int dy)
{
    if (d == 1) {
        paint(x, y, '+');
        paint(x + dx, y + dy, dx == 0 ? '-' : '|');
        paint(x + dx * 2, y + dy * 2, '+');
        return;
    }

    int L = len[d];
    int dxl = dx, dyl = dy;
    lRot(dxl, dyl);
    int dxr = dx, dyr = dy;
    rRot(dxr, dyr);
    if (!intersect(LX, RX, x, x + dx * L, x + dxl * sum[d-1]) && !intersect(LY, RY, y, y + dy * L, y + dyl * sum[d-1]))
        return;

    L = len[d-1];
    go(d - 1, x, y, dx, dy);
    x += dx * L, y += dy * L;

    go(d - 1, x, y, dxl, dyl);
    x += dxl * L, y += dyl * L;

    go(d - 1, x, y, dx, dy);
    x += dx * L, y += dy * L;

    go(d - 1, x, y, dxr, dyr);
    x += dxr * L, y += dyr * L;

    go(d - 1, x, y, dx, dy);
    x += dx * L, y += dy * L;
}

int main()
{
    len[1] = 2;
    for (int i = 2; i < maxn; i++)
        len[i] = len[i-1] * 3;
    sum[0] = 0;
    for (int i = 1; i < maxn; i++)
        sum[i] = sum[i-1] + len[i];
    int T, cas = 0;
    scanf("%d", &T);
    while (T--) {
        printf("Case %d:\n", ++cas);
        int depth;
        scanf("%d%d%d", &depth, &LX, &LY);
        RX = LX + maxl - 1;
        RY = LY + maxl - 1;
        int x = sum[depth - 1], y = sum[depth - 1];
        memset(a, '.', sizeof(a));
        int L = len[depth];
        go(depth, x, y, 0, 1);
        go(depth, x, y + L, 1, 0);
        go(depth, x + L, y + L, 0, -1);
        go(depth, x + L, y, -1, 0);
        for (int i = 0; i < maxl; i++) {
            for (int j = 0; j < maxl; j++)
                putchar(a[i][j]);
            puts("");
        }
    }
}
