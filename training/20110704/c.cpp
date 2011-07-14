#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

int tests;
long long A[600][600], B[600][600], C[600][600], D[600][600];
long long a[600], b[600], sa[600], sb[600];
int r, c, q;

inline long long query(long long *s, int a, int b) {
	return s[b] - s[a - 1];
}

long long proceed(long long *a, long long *s, int l, int r) {
	long long ans = 0, tmp = 0;
	for (int i = l; i <= r; ++ i)
		tmp += a[i] * (i - l);
	ans = tmp;
	for (int i = l + 1; i <= r; ++ i) {
		tmp -= query(s, i, r);
		tmp += query(s, l, i - 1);
		ans = min(ans, tmp);
	}
	return ans;
}

int main() {
	cin >> tests;
	int ca = 0;
	while (tests --) {
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		memset(sa, 0, sizeof(sa));
		memset(sb, 0, sizeof(sb));
		memset(A, 0, sizeof(A));
		memset(C, 0, sizeof(C));
		memset(D, 0, sizeof(D));
//		scanf("%d%d%d", &r, &c, &q);
		cin >> r >> c >> q;
		for (int i = 1; i <= r; ++ i)
			for (int j = 1; j <= c; ++ j)
				cin >> A[i][j];
		for (int i = 1; i <= r; ++ i)
			for (int j = 1; j <= c; ++ j)
				C[i][j] = C[i][j - 1] + A[i][j];
		for (int i = 1; i <= c; ++ i)
			for (int j = 1; j <= r; ++ j)
				D[i][j] = D[i][j - 1] + A[j][i];
//		printf("Test Case %d:\n", ++ ca);
		cout << "Test Case " << ++ ca << ":" << endl;
		for (int i = 0; i < q; ++ i) {
			memset(sa, 0, sizeof(sa));
			memset(sb, 0, sizeof(sb));
			int r1, r2, c1, c2;
//			scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
			cin >> r1 >> c1 >> r2 >> c2;
			for (int j = r1; j <= r2; ++ j)
				a[j] = query(C[j], c1, c2), sa[j] = sa[j - 1] + a[j];
			for (int j = c1; j <= c2; ++ j)
				b[j] = query(D[j], r1, r2), sb[j] = sb[j - 1] + b[j];
			cout << i + 1 << ' ' << proceed(a, sa, r1, r2) + proceed(b, sb, c1, c2) << endl;
		}
		puts("");
	}
	return 0;
}

