#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <string>
using namespace std;

string url[11];
int n = 11;
int tests;
typedef pair<int, int> PII;
PII r[11];

int main() {
	cin >> tests;
	int ca = 0;
	while (tests --) {
		printf("Case #%d:\n", ++ ca);
		for (int i = 0; i < n; ++ i) {
			cin >> url[i] >> r[i].first;
			r[i].first *= -1;
			r[i].second = i;
		}
		sort(r, r + n);
		for (int i = 0; i < n; ++ i)
			if (r[i].first == r[0].first)
				cout << url[r[i].second] << endl;
	}
	return 0;
}

