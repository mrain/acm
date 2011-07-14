#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

struct TState {
    int a[20], b[20];
    TState() {
        memset(a, 0xFF, sizeof(a));
        memset(b, 0xFF, sizeof(b));
    }
    void set(int i, int p, int q) {
        a[i] = p, b[i] = q;
    }
};

int n, m, h, t, ans;
char A[21][21];
bool cutr[21][21][21], cutc[21][21][21];
TState q[20000];
bool map[21][21];

TState reverse(const TState &st) {
    memset(map, 0, sizeof(map));
    for (int i = 0; i < 20; ++ i) {
        if (st.a[i] < 0) continue;
        for (int j = st.a[i]; j <= st.b[i]; ++ j)
            map[j][i] = true;
    }
    TState a;
    for (int i = 0; i < 20; ++ i) {
        int A = 200, B = -1;
        for (int j = 0; j < 20; ++ j)
            if (map[i][j]) {
                A = min(A, j);
                B = max(B, j);
            }
        if (B >= 0) a.set(i, A, B);
    }
    return a;
}

void output(const TState &st) {
	for (int i = 0; i < n; ++ i) {
		if (st.a[i] == -1) {
			for (int j = 0; j < m; ++ j) cout << '*';
			cout << endl;
			continue;
		}
		for (int j = 0; j < st.a[i]; ++ j) cout << '*';
		for (int j = st.a[i]; j <= st.b[i]; ++ j) cout << A[i][j];
		for (int j = st.b[i] + 1; j < m; ++ j) cout << '*';
		cout << endl;
	}
}

inline void push(const TState &st) {
    q[t ++] = st;
    if (t == 20000) t = 0;
}

void expand(const TState &st) {
    TState a, b, rev = reverse(st);
    //cut row
    for (int i = 1; i < n; ++ i) {
        int A = st.a[i - 1], B = st.b[i - 1];
        if (st.a[i] < 0 || st.b[i] < 0) continue;
        if (A >= 0 && B >= 0 && cutr[i][A][B]) {
            for (int j = 0; j < i; ++ j)
                a.set(j, st.a[j], st.b[j]);
            for (int j = i; j < n; ++ j)
                b.set(j, st.a[j], st.b[j]);
            push(a); push(b);
            return;
        }
    }
    //cut col
    for (int i = 1; i < m; ++ i) {
        int A = rev.a[i - 1], B = rev.b[i - 1];
        if (rev.a[i] < 0 || rev.b[i] < 0) continue;
        if (A >= 0 && B >= 0 && cutc[i][A][B]) {
            for (int j = 0; j < i; ++ j)
                a.set(j, rev.a[j], rev.b[j]);
            for (int j = i; j < m; ++ j)
                b.set(j, rev.a[j], rev.b[j]);
            push(reverse(a));
            push(reverse(b));
            return;
        }
    }
    bool flag = false, uflag, dflag, u, d, l, r;
    for (int i = 1; i < n; ++ i)
        for (int j = 1; j < m; ++ j) {
            //deal flag
            u = l = d = r = false;
            uflag = st.a[i - 1] < j && st.b[i - 1] >= j;
            dflag = st.a[i] < j && st.b[i] >= j;
            if (uflag && dflag) {
                l = cutr[i][st.a[i - 1]][min(j - 1, st.b[i - 1])];
                u = cutc[j][rev.a[j - 1]][min(i - 1, rev.b[j - 1])];
                r = cutr[i][max(j, st.a[i])][st.b[i]];
                d = cutc[j][max(i, rev.a[j])][rev.b[j]];
            }
            // ul
            if (u && l) {
                for (int k = i; k < n; ++ k)
                    b.set(k, st.a[k], st.b[k]);
                for (int k = 0; k < i; ++ k) {
                    if (st.a[k] >= j)
                        a.set(k, -1, -1), b.set(k, st.a[k], st.b[k]);
                    else if (st.b[k] < j)
                        b.set(k, -1, -1), a.set(k, st.a[k], st.b[k]);
                    else {
                        a.set(k, st.a[k], j - 1);
                        b.set(k, j, st.b[k]);
                    }
                }
                push(a); push(b);
                return;
            }
            if (d && r) {
                for (int k = 0; k < i; ++ k)
                    a.set(k, st.a[k], st.b[k]);
                for (int k = i; k < n; ++ k) {
                    if (st.a[k] >= j)
                        a.set(k, -1, -1), b.set(k, st.a[k], st.b[k]);
                    else if (st.b[k] < j)
                        b.set(k, -1, -1), a.set(k, st.a[k], st.b[k]);
                    else {
                        a.set(k, st.a[k], j - 1);
                        b.set(k, j, st.b[k]);
                    }
                }
                push(a); push(b);
                return;
            }
            if (u && r) {
                for (int k = i; k < n; ++ k)
                    b.set(k, st.a[k], st.b[k]);
                for (int k = 0; k < i; ++ k) {
                    if (st.a[k] >= j)
                        b.set(k, -1, -1), a.set(k, st.a[k], st.b[k]);
                    else if (st.b[k] < j)
                        a.set(k, -1, -1), b.set(k, st.a[k], st.b[k]);
                    else {
                        b.set(k, st.a[k], j - 1);
                        a.set(k, j, st.b[k]);
                    }
                }
                push(a); push(b);
                return;
            }
            if (d && l) {
                for (int k = 0; k < i; ++ k)
                    a.set(k, st.a[k], st.b[k]);
                for (int k = i; k < n; ++ k) {
                    if (st.a[k] >= j)
                        b.set(k, -1, -1), a.set(k, st.a[k], st.b[k]);
                    else if (st.b[k] < j)
                        a.set(k, -1, -1), b.set(k, st.a[k], st.b[k]);
                    else {
                        b.set(k, st.a[k], j - 1);
                        a.set(k, j, st.b[k]);
                    }
                }
                push(a); push(b);
                return;
            }
        }
    flag = false;
    for (int i = 0; i < n; ++ i)
        if (st.a[i] >= 0) {
            flag = true;
            break;
        }
    if (!flag) return;
    ++ ans;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i)
        scanf("%s", A[i]);
    memset(cutr, 0, sizeof(cutr));
    memset(cutc, 0, sizeof(cutc));
    for (int i = 1; i < n; ++ i) {
        for (int a = 0; a < m; ++ a) {
            cutr[i][a][a] = (A[i][a] != A[i - 1][a]);
            for (int b = a + 1; b < m; ++ b)
                cutr[i][a][b] = cutr[i][a][b - 1] && (A[i][b] != A[i - 1][b]);
        }
    }
    for (int i = 1; i < m; ++ i) {
        for (int a = 0; a < n; ++ a) {
            cutc[i][a][a] = (A[a][i] != A[a][i - 1]);
            for (int b = a + 1; b < n; ++ b)
                cutc[i][a][b] = cutc[i][a][b - 1] && (A[b][i] != A[b][i - 1]);
        }
    }
    TState now;
    for (int i = 0; i < n; ++ i)
        now.set(i, 0, m - 1);
    h = t = 0;
    q[t ++] = now;
    while (h != t) {
        TState now = q[h ++];
        if (h == 20000) h = 0;
        expand(now);
    }
    printf("%d\n", ans);
	/*freopen("temp.txt", "w", stdout);
	for (int i = 0; i < h; ++ i) {
		cout << i << endl;
		output(q[i]);
	}*/
    return 0;
}

