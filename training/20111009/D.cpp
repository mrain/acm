#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>

using namespace std;

#define maxn (300000)

/*typedef pair<int, int> PII;*/

int g[maxn], a[maxn], b[maxn];

void work() {
	int N; scanf("%d", &N);
	//map<int, int> hash;
	for (int i = 0; i < N; ++i) {
		scanf("%d", &g[i]);/* hash[g[i]] = -1;*/	
	}
/*
	int n = 0;
	for (map<int, int>::iterator it = hash.begin(); it != hash.end(); ++it) it -> second = n++;
	
	for (int i = 0; i < N; ++i) g[i] = hash[g[i]];
*/	
	memset(a, 0, sizeof(a)); memset(b, 0, sizeof(b));
	
	a[0] = 1;
	for (int i = 1; i < N; ++i) {
		if (g[i] > g[i - 1]) a[i] = a[i - 1] + 1;
		else a[i] = 1;
	}
	
	b[N - 1] = 1;
	for (int i = N - 2; i >= 0; --i) {
		if (g[i] < g[i + 1]) b[i] = b[i + 1] + 1;
		else b[i] = 1;
	}	
	
	//for (int i = 0; i < N; ++i) printf("%d %d\n", a[i], b[i]);
	
	int ans = 0;
	/*set<PII> f; f.clear();*/
	vector<int> f; f.clear();
	for (int i = 0; i < N; ++i) {
		vector<int>::iterator it = lower_bound(f.begin(), f.end(), g[i]);
		ans = max(ans, (int)(it - f.begin()) + b[i]);
		if (f.size() < a[i]) f.push_back(g[i]);
		else f[a[i] - 1] = min(g[i], f[a[i] - 1]);
		/*
		for (int j = 0; j < (int)f.size(); ++ j)
			printf("%d ", f[j]);
		puts("");
		*/
	}
	
	printf("%d\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	
	while (T--) work();

	return 0;
}	
