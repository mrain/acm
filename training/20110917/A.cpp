#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (5000005)

const int bound = 5000000;
int f[maxn];
int g[200000];

int main() {
	for (int i = 2; i <= bound; ++i) if (!f[i]) 
		for (int k = i; k <= bound; k += i) f[k] = i;
		
	int n, cases = 0;
	while (scanf("%d", &n) == 1) {
		printf("Test #%d: ", ++cases);
	
		for (int i = 1; i <= n; ++i) scanf("%d", &g[i]);
		for (int i = 1; i <= n; ++i) {
			int x = g[i], cnt = 0;
			while (x != 1) cnt++, x /= f[x];
			g[i] = cnt;
		}
		
		int sum = 0;
		for (int i = 1; i <= n; ++i) sum ^= g[i];
		
		if (sum == 0) {
			puts("Bob"); continue;
		}
	
		for (int i = 1; i <= n; ++i) {
			int x = sum ^ g[i];
			
			if (g[i] >= x) {
				printf("Alice %d\n", i);
				break;
			}		
		} 
	}

	return 0;
}

/*
Sample Input

4
5 7 9 12
4
41503 15991 72 16057 

Sample Output

Test #1: Alice 1
Test #2: Bob
*/
