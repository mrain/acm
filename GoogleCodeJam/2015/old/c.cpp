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

const int CAPA = 500000;

bool isprime[500010], vis[1010], check[1010];
int prime[500010], cnt;
int T, n, a[1010], matching[1010];
vector <int> e[1010];

bool dfs(int u) {
	for (int i = 0; i < e[u].size(); ++ i) {
		int v = e[u][i];
		if (!check[v]) {
			check[v] = true;
			if (matching[v] == -1 || dfs(matching[v])) {
				matching[v] = u;
				matching[u] = v;
				return true;
			}
		}
	}
	return false;
}

void generate() {
	cnt = 0;
	for (int i = 2; i <= CAPA; ++ i)
		isprime[i] = true;
	for (int i = 2; i <= CAPA; ++ i) {
		if (isprime[i]) {
			prime[cnt ++] = i;
		}
		for (int j = 0; j < cnt && (long long)prime[j] * i <= CAPA; ++ j) {
			isprime[prime[j] * i] = false;
			if (i % prime[j] == 0) break;
		}
	}
	//cout << prime[0] << ' ' << prime[1] << ' ' << prime[2] << endl;
}

int main() {
	generate();
	cin >> T;
	for (int t = 1; t <= T; ++ t) {
		cin >> n;
		for (int i = 0; i < n; ++ i) {
			cin >> a[i];
			e[i].clear();
		}
		sort(a, a + n);
		for (int i = 0; i < n; ++ i) {
			for (int j = i + 1; j < n; ++ j) {
				if (a[j] % a[i] != 0) continue;
				if (isprime[a[j] / a[i]]) {
					//cout << a[i] << ' ' << a[j] << endl;
					e[i].push_back(j);
					e[j].push_back(i);
				}
			}
		}
		int ans = n;
		memset(matching, 0xFF, sizeof(matching));
		for (int i = 0; i < n; ++ i) {
			if (matching[i] == -1) {
				memset(check, 0, sizeof(check));
				if (dfs(i))
					-- ans;
			}
		}
		printf("Case #%d: %d\n", t, ans);
	}
    return 0;
}
