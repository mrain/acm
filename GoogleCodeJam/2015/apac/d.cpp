#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

int tests, cnt, m;
int s[100];

void cut2(int a, int b) {
	if (b > a) swap(a, b);
	if (b == 0) return;
	if (cnt == 0) return;
	for (int i = 30; i >= 0; -- i) {
		if ((1 << i) <= b && s[i] > 0) {
			-- s[i]; -- cnt;
			//cout << a << " " << b << " " << i << endl;
			cut2(a - (1 << i), b);
			cut2((1 << i), b - (1 << i));
			break;
		}
	}
}

void cut(int size) {
	if (cnt == 0 || size == 0) return;
	int h = 1, t = 0;
	for (int i = 0; i < 31; ++ i) {
		if (((long long)h) * 2ll > size) break;
		h *= 2; t += 1;
	}
	
	/* big block */
	if (s[t] > 0) { 
		//cout << size << " " << h << " " << t << endl;
		-- s[t]; -- cnt; 
	} else {
		cut(h / 2); cut(h / 2);
		cut(h / 2); cut(h / 2);
		if (cnt == 0) return;
	}

	if (m == h) return;
	/* small ones */
	cut(size - h); 
	if (cnt == 0) return;
	int a = h, b = m - h;
	while (b) {
		int t = a / b;
		for (int i = 0; i < 2 * t; ++ i)
			cut(b);
		a = b;
		b = a - b;
	}
}

int main() {
	cin >> tests;
	for (int cases = 1; cases <= tests; ++ cases) {
		memset(s, 0, sizeof(s));
		cin >> cnt >> m;
		for (int i = 0; i < cnt; ++ i) {
			int a;
			cin >> a;
			s[a] ++;
		}

		int ans = 0;
		while (cnt) {
			++ ans;
			cut2(m, m);
		}
		printf("Case #%d: %d\n", cases, ans);
	}
    return 0;
}
