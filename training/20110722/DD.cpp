#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int n,p,a,b;

int main() {

	while (scanf("%d%d%d%d",&n,&p,&a,&b)==4&&(n+p+a+b)) 
		printf("%f\n",((double)(n-1))*(((double)p)/100.)*((double)min(a,b)));

	return 0;
}
