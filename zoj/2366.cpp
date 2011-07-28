#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

const int inf = 0x7FFFFFFF;
int tests, n, m, z;
int rank[500];
string alphabet, sa, sb;
int a[2010], b[2010];
int f[2010][2010];
int d[201][201], dx[201], dy[201], ax[201], ay[201];
string ans1, ans2;

void genans(int i, int j) {
	if (i == 0 && j == 0) return;
	int A = inf, B = inf, C = inf;
	if (i) A = f[i - 1][j] + dx[a[i]];
	if (j) B = f[i][j - 1] + dy[b[j]];
	if (i && j) C = f[i - 1][j - 1] + d[a[i]][b[j]];
	if (A <= B && A <= C) {
		ans1.push_back(alphabet[a[i]]);
		ans2.push_back(alphabet[ax[a[i]]]);
		genans(i - 1, j);
	} else if (B <= A && B <= C) {
		ans1.push_back(alphabet[ay[b[j]]]);
		ans2.push_back(alphabet[b[j]]);
		genans(i, j - 1);
	} else if (C <= A && C <= B) {
		ans1.push_back(alphabet[a[i]]);
		ans2.push_back(alphabet[b[j]]);
		genans(i - 1, j - 1);
	}
}

int main() {
	cin >> tests;
	while (tests --) {
		memset(rank, 0, sizeof(rank));
		cin >> alphabet >> sa >> sb;
		z = alphabet.length(); n = sa.length(); m = sb.length();
		for (int i = 0; i < z; ++ i)
			rank[(int)alphabet[i]] = i;
		for (int i = 1; i <= n; ++ i) a[i] = rank[(int)sa[i - 1]];
		for (int i = 1; i <= m; ++ i) b[i] = rank[(int)sb[i - 1]];
		memset(dx, 0x3F, sizeof(dx));
		memset(dy, 0x3F, sizeof(dy));
		memset(ax, 0, sizeof(ax));
		memset(ay, 0, sizeof(ay));
		for (int i = 0; i < z; ++ i)
			for (int j = 0; j < z; ++ j) {
				cin >> d[i][j];
				if (dx[i] > d[i][j]) dx[i] = d[i][j], ax[i] = j;
				if (dy[j] > d[i][j]) dy[j] = d[i][j], ay[j] = i;
			}
		f[0][0] = 0;
		for (int i = 0; i <= n; ++ i)
			for (int j = 0; j <= m; ++ j) {
				if (i == 0 && j == 0) continue;
				f[i][j] = 0x7FFFFFFF;
				if (i) f[i][j] = min(f[i][j], f[i - 1][j] + dx[a[i]]);
				if (j) f[i][j] = min(f[i][j], f[i][j - 1] + dy[b[j]]);
				if (i && j)
					f[i][j] = min(f[i][j], f[i - 1][j - 1] + d[a[i]][b[j]]);
			}
		ans1.clear(); ans2.clear();
		cout << f[n][m] << endl;
		genans(n, m);
		reverse(ans1.begin(), ans1.end());
		reverse(ans2.begin(), ans2.end());
		cout << ans1 << endl << ans2 << endl;
	}
	return 0;
}

