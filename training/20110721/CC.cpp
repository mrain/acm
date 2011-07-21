#include<cstdio>
int main()
{
	freopen("CCC.cpp","w",stdout);
	for (int k=0;k<3;k++)
		for (int i=0;i<2;i++) {
			for (int j=0;j<3;j++)
				printf("ret.g[%d][%d]+=a.g[%d][%d]*b.g[%d][%d];\n",i,j,i,k,k,j);
		}
	return 0;
}
