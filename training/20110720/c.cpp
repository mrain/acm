#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

typedef pair<int, int> PII;
bool cmp(const PII &a, const PII &b) {
	return a.first * a.second < b.first * b.second;
}
vector <PII> a;
int n, w, d;

void cut(const PII &t, int s, int i) {
	int w = t.first , d = t.second;
	s %= w + d;
	PII p, q;
	if (s < w) {
		p = (make_pair(s, d));
		q = (make_pair(w - s, d));
	} else if (s < w + d) {
		p = (make_pair(w, s - w));
		q = (make_pair(w, d - s + w));
	}
	if (cmp(q, p)) swap(p, q);
//	a[i] = p;
//	a.insert(a.begin() + i + 1, q);
	a.push_back(p);
	a.push_back(q);
}

int main() {
	while (scanf("%d%d%d", &n, &w, &d) == 3 && (n || w || d)) {
		a.clear();
		a.push_back(make_pair(w, d));
		for (int i = 0; i < n; ++ i) {
			int p, s;
			scanf("%d%d", &p, &s);
			-- p;
			PII t = a[p];
			a.erase(a.begin() + p);
			cut(t, s, p);
/*			for (int j = 0; j <= i + 1; ++ j)
				printf("(%d,%d) ", a[j].first, a[j].second);
			cout << endl;*/
		}
		sort(a.begin(), a.end(), cmp);
		for (int i = 0; i < n; ++ i)
			printf("%d ", a[i].first * a[i].second);
		printf("%d\n", a[n].first * a[n].second);
	}
	return 0;
}

