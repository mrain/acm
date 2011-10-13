#include <cstdio>

using namespace std;

int main() {
	int T; scanf("%d", &T);
	
	for (int t = 1; t <= T; ++t) {
		printf("Case #%d: ", t);
		int m, k; scanf("%d%d", &m, &k);
		printf("%.8f\n", 1. / ((double) (m * k + k + 1)));
	}
	
	return 0;
}
