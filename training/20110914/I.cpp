#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define maxn (1005)

int n;
int sum[maxn];

bool gao(int x) {
	sum[x]--;
	
	vector<int> tmp; tmp.clear();
	
	int k = x;
	while (x > 0 && k > 0) {
		while (sum[k] > 0 && x > 0) tmp.push_back(k - 1), sum[k]--, x--;
		k--;
	}
	
	if (x > 0) return false;
	
	for (int i = 0; i < tmp.size(); ++i) if (tmp[i] > 0) sum[tmp[i]]++;
	return true; 
}

void work() {
	scanf("%d", &n);
	memset(sum, 0, sizeof(sum));
	
	for (int i = 1; i <= n; ++i) {
		int x; scanf("%d", &x);
		if (x > n) {
			puts("no"); return ;
		}
		
		sum[x]++;
	}
	
	int k = n;
	while (k > 0) {
		while (sum[k] > 0) if (!gao(k)) {
			puts("no"); return ;
		}
		k--;
	}
	
	puts("yes");
}

int main() {
	int T; scanf("%d", &T);
	
	while (T--) work();

	return 0;
}
