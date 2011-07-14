#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, a[100010], b[100010];

bool allsame() {
	for (int i = 1; i < n; ++ i)
		if (a[i] != a[0]) return false;
	return true;
}

void mk() {
	for (int i = 0; i < n; ++ i) {
		b[(i + 1) % n] = a[i] / 2;
		a[i] /= 2;
	}
	for (int i = 0; i < n; ++ i) {
		a[i] += b[i];
		if ((a[i] & 1) == 1) ++ a[i];
	}
}

int main() {
	while (1) {
		scanf("%d", &n);
		if (!n) break;
		for (int i = 0; i < n; ++ i) scanf("%d", a + i);
		int cnt = 0;
		while (!allsame()) {
			++ cnt;
			mk();
		}
		cout << cnt << ' ' << a[0] << endl;
	}
	return 0;
}

