#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <cmath>
#include <cctype>
using namespace std;

int n, t;
int A[51];
vector <long long> unit;

template <class T>
T gcd(T a, T b) {
	return b == 0 ? a : gcd(b, a % b);
}

template <class T>
T lcm(T a, T b) {
	return a / gcd(a, b) * b;
}

long long mk(long long a, long long b, long long c, long long d) {
	return lcm(a, lcm(b, lcm(c, d)));
}

int main() {
	while (1) {
		cin >> n >> t;
		if (n == 0 && t == 0) break;
		for (int i = 0; i < n; ++ i) cin >> A[i];
		unit.clear();
		for (int a = 0; a < n; ++ a)
			for (int b = a + 1; b < n; ++ b)
				for (int c = b + 1; c < n; ++ c)
					for (int d = c + 1; d < n; ++ d)
						unit.push_back(mk(A[a], A[b], A[c], A[d]));
		sort(unit.begin(), unit.end());
		unit.erase(unique(unit.begin(), unit.end()), unit.end());
		for (int T = 0; T < t; ++ T) {
			long long d;
			cin >> d;
			long long a1 = 0, a2 = 1000000000000000ll;
			for (int i = 0; i < (int)unit.size(); ++ i) {
				long long p = d / unit[i];
				a1 = max(unit[i] * p, a1);
				if (d % unit[i] == 0) a2 = d;
				a2 = min(unit[i] * (p + 1), a2);
			}
			cout << a1 << ' ' << a2 << endl;
		}
	}
	return 0;
}

