#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;

int tests, n;
long long f[1010];

int main() {
	memset(f, 0, sizeof(f));
	f[0] = 1;
	for (int i = 1; i <= 1000; ++ i)
		for (int j = 0; j * 2 <= i; ++ j)
			f[i] += f[j];
	scanf("%d", &tests);
	int ca = 0;
	while (tests --) {
		scanf("%d", &n);
		cout << ++ ca << ' ' << f[n] << endl;
	}
	return 0;
}

