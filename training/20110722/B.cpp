#include<cstdio>
#include<cmath>
const double Pi=acos(-1.);
int main()
{
	int l;
	while(scanf("%d",&l),l)
		printf("%.2f\n",(double(l)/Pi)*(double(l)/Pi)*Pi/2.0);
	return 0;
}
