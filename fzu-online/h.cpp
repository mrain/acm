#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#define Pnt(x) (tree[x].pnt)
#define Lch(x) (tree[x].lch)
#define Rch(x) (tree[x].rch)
#define Data(x) (tree[x].data)
#define Sum(x) (tree[x].sum)
#define Lmax(x) (tree[x].lmax)
#define Lmin(x) (tree[x].lmin)
#define Rmax(x) (tree[x].rmax)
#define Rmin(x) (tree[x].rmin)
#define FlagInv(x) (tree[x].invert)
#define FlagRev(x) (tree[x].reverse)
#define FlagCov(x) (tree[x].cover)

struct SplayNode {
    int pnt, lch, rch;
    int data, sum, lmax, rmax, lmin, rmin;
    bool invert, reverse, cover;
}tree[50010];
int tests, n, m, root;
char str[50010];

void reverse(int cur) {
    if (!FlagRev(cur)) return;
    swap(Lmax(cur), Rmax(cur));
    swap(Lmin(cur), Rmin(cur));
    Sum(cur) = -Sum(cur);
    if (Lch(cur) > 0) FlagRev(Lch(cur)) ^= 1;
    if (Rch(cur) > 0) FlagRev(Rch(cur)) ^= 1;
    FlagRev(cur) = false;
}

void invert(int cur) {
    if (!FlagInv(cur)) return;
    swap(Lmax(cur), Lmin(cur));
    Lmax(cur) = -Lmax(cur); Lmin(cur) = -Lmin(cur);
    swap(Rmax(cur), Rmin(cur));
    Rmax(cur) = -Rmax(cur); Rmin(cur) = -Rmin(cur);
    Sum(cur) = -Sum(cur);
    if (Lch(cur) > 0) FlagInv(Lch(cur)) ^= 1;
    if (Rch(cur) > 0) FlagInv(Rch(cur)) ^= 1;
    FlagInv(cur) = false;
}

void Cover(int cur) {
    if (!FlagCov(cur)) return;
}

void update(int cur) {
    reverse(cur); invert(cur);
    if (Lch(cur) > 0) reverse(Lch(cur)), invert(Lch(cur));
    if (Rch(cur) > 0) reverse(Rch(cur)), invert(Rch(cur));
    Sum(cur) = Sum(Lch(cur)) + Sum(Rch(cur));
}

int zig(int cur) {
    if (!Pnt(cur)) return cur;
    int pnt = Pnt(cur), anc = Pnt(pnt), tmp;
}

int zag(int cur) {
}

int splay(int cur) {
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &tests);
    while (tests --) {
        scanf("%d%d", &n, &m);
        scanf("%s", str);
        memset(tree, 0, sizeof(tree));
        Sum(0) = Lmax(0) = Rmax(0) = -2147483647;
        Lmin(0) = Rmin(0) = 2147483647;
        for (int i = 1; i <= n; ++ i) {
            Pnt(i) = tree[i].lch = tree[i].rch = -1;
            tree[i].data = (str[i - 1] == '(') ? 1 : -1;
            tree[i].sum = tree[i].lmax = tree[i].lmin = tree[i].data;
            tree[i].rmax = tree[i].rmax = tree[i].data;
        }
        root = 1;
        for (int i = 1; i <= n; ++ i) {
        }
    }
}
