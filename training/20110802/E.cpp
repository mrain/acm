#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
	int n,cases=0;

	while (scanf("%d",&n)==1&&n) {
		printf("Case %d:\n",++cases);
		printf("%d pencils for %d cents\n",n,n);
	
		n*=4;
		
		int cnt=0;
		for (int i=1;i<=n;i++) {
			int A=i*16;
			if (A>=n) break;
			for (int j=1;j<=n;j++) {
				int B=A+j+j;
				if (B>=n) break;
					
				int k=n-B; 
				
				if (i+j+k!=n/4) continue;
				
				cnt++;
				
				printf("%d at four cents each\n",i);
				printf("%d at two for a penny\n",j);
				printf("%d at four for a penny\n",k);
				
				puts("");
			}
		}
		
		if (!cnt) puts("No solution found.\n");
	}

	return 0;
}

/*
No solution found.

Case 2:
20 pencils for 20 cents
3 at four cents each
15 at two for a penny
2 at four for a penny

*/
