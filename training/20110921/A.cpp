#include <cstdio>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define maxn (100000)

typedef long long LL;

struct ele {
	int x, y, z, a, b, c;
} g[maxn];

struct cmpz {
	bool operator() (const int &a, const int &b) {
		return g[a].z < g[b].z;
	}
};

struct cmpy {
	bool operator() (const int &a, const int &b) {
		return g[a].y < g[b].y;
	}
};

multiset<int, cmpz> Z;
multiset<int, cmpy> Y;
int X[maxn];
int n, m;
LL A, B, C;

bool cmp(int a, int b) {
	return g[a].x < g[b].x;
}

void work() {
	for (int i = 1; i <= n; ++i) g[i].a = g[i].b = g[i].c = g[i].x = g[i].y = g[i].z = 0;

	if (m > 0) for (int i = 1; i <= n; ++i) scanf("%d", &g[i].a);
	if (m > 1) for (int i = 1; i <= n; ++i) scanf("%d", &g[i].b);
	if (m > 2) for (int i = 1; i <= n; ++i) scanf("%d", &g[i].c);
	
	if (m > 0) for (int i = 1; i <= n; ++i) scanf("%d", &g[i].x);
	if (m > 1) for (int i = 1; i <= n; ++i) scanf("%d", &g[i].y);
	if (m > 2) for (int i = 1; i <= n; ++i) scanf("%d", &g[i].z);
	
	int tmp; A = B = C = 0ll;
	if (m > 0) {
		scanf("%d", &tmp); A = tmp;
	}
	if (m > 1) {
		scanf("%d", &tmp); B = tmp;
	}
	if (m > 2) {
		scanf("%d", &tmp); C = tmp;
	}
	
	for (int i = 1; i <= n; ++i) X[i] = i;
	sort(X + 1, X + 1 + n, cmp);
	Y.clear(); Z.clear();
	
	for (int t = 1, i = 1; t <= n; ++t) {
		//printf("%d %d %d fuck1\n", Y.size(), Z.size(), i);
		while (i <= n && (LL) g[X[i]].x <= A) Y.insert(X[i++]);
		//printf("%d %d %d fuck2\n", Y.size(), Z.size(), i);
		while (Y.begin() != Y.end() && (LL) g[*Y.begin()].y <= B) {
			Z.insert(*Y.begin()); Y.erase(Y.begin());
		}
		//printf("%d %d fuck3\n", Y.size(), Z.size());
		
		if (Z.begin() == Z.end() || (LL) g[*Z.begin()].z > C) {
			puts("No"); return ;
		}
		//printf("%d %d fuck4\n", Y.size(), Z.size());
		
		int k = *Z.begin(); Z.erase(Z.begin());
		A += (LL) g[k].a, B += (LL) g[k].b, C += (LL) g[k].c;
		//printf("%d %d %d %d %lld %lld %lld\n", k, i, Y.size(), Z.size(), A, B, C);
	}

	puts("Yes");
}

int main() {
	while (scanf("%d%d", &n, &m) == 2) work();
	
	return 0;
}
