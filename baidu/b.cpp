#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

int a, b, n, ans;
int cover1[300][300], cover2[300][300];
int A[300][300], s[300][300];
int minr[300], minc[300];
int minrr[300], mincc[300];
int hr[300], hc[300];

int getarea(int x1, int y1, int x2, int y2) {
	return s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1];
}

int main() {
	while (1) {
		memset(A, 0, sizeof(A));
		memset(s, 0, sizeof(s));
		scanf("%d%d", &a, &b);
		if (a == 0 && b == 0) break;
		scanf("%d", &n);
		++ a, ++ b;
		for (int i = 0; i < n; ++ i) {
			int p, q;
			scanf("%d%d", &p, &q);
			++ p; ++ q;
			A[p][q] = 1;
		}
		for (int i = 1; i <= a; ++ i)
			for (int j = 1; j <= b; ++ j)
				s[i][j] = A[i][j] + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
		memset(cover1, 0x1F, sizeof(cover1));
		memset(cover2, 0x1F, sizeof(cover2));
		memset(minr, 0x1F, sizeof(minr));
		memset(minc, 0x1F, sizeof(minc));
		memset(minrr, 0x1F, sizeof(minrr));
		memset(mincc, 0x1F, sizeof(mincc));
		for (int i = 1; i <= a; ++ i)
			for (int j = 1; j <= b; ++ j) {
				if (i + 28 <= a && j + 15 <= b)
					cover1[i][j] = getarea(i + 1, j + 1, i + 28 - 1, j + 15 - 1);
				if (i + 15 <= a && j + 28 <= b)
					cover2[i][j] = getarea(i + 1, j + 1, i + 15 - 1, j + 28 - 1);
			}
		for (int i = 1; i <= a; ++ i)
			for (int j = 1; j <= b; ++ j) {
				minr[i] = min(minr[i], min(cover1[i][j], cover2[i][j]));
				minc[j] = min(minc[j], min(cover1[i][j], cover2[i][j]));
				minrr[i + 28] = min(minrr[i + 28], cover1[i][j]);
				minrr[i + 15] = min(minrr[i + 15], cover2[i][j]);
				mincc[j + 28] = min(mincc[j + 28], cover2[i][j]);
				mincc[j + 15] = min(mincc[j + 15], cover1[i][j]);
			}

		memset(hr, 0x1F, sizeof(hr));
		memset(hc, 0x1F, sizeof(hc));
		for (int i = 1; i <= a; ++ i)
			hr[i] = min(hr[i - 1], minrr[i]);
		for (int i = 1; i <= b; ++ i)
			hc[i] = min(hc[i - 1], mincc[i]);
		int cr = 0x1F1F1F1F, cc = 0x1F1F1F1F;
		ans = n;
		for (int i = a; i; -- i) {
			cr = min(cr, minr[i]);
			//cout << hr[i] << ' ' << cr << endl;
			ans = min(ans, cr + hr[i]);
		}
		for (int i = b; i; -- i) {
			cc = min(cc, minc[i]);
			//cout << hc[i] << ' ' << cc << endl;
			ans = min(ans, cc + hc[i]);
		}
		cout << ans << endl;
	}
	return 0;
}

