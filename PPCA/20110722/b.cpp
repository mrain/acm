#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

const int offset = 150000;
int f[300010];
int n, a[101], b[101];

inline int &g(int i) { return f[i + offset]; }

int main() {
	memset(f, 0xE0, sizeof(f));
	g(0) = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i)
		scanf("%d%d", a + i, b + i);
	int up = 100001, lo = -100001;
	for (int i = 0; i < n; ++ i) {
		if (a[i] > 0) {
			for (int j = up; j >= lo; -- j)
				if (g(j + a[i]) < g(j) + b[i])
					g(j + a[i]) = g(j) + b[i];
		} else {
			for (int j = lo; j <= up; ++ j)
				if (g(j + a[i]) < g(j) + b[i])
					g(j + a[i]) = g(j) + b[i];
		}
	}
	int ans = 0;
	for (int i = lo; i <= up; ++ i)
		if (i >= 0 && g(i) >= 0 && ans < i + g(i)) ans = i + g(i);
	cout << ans << endl;
	return 0;
}

