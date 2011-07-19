#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
const int MX=2003;
int n;
bool worm[MX];
vector<int> e[MX];
double A[MX],B[MX];
int son[MX];
bool vis[MX];
void DP(int u)
{
	son[u]=0;
	if(e[u].size())
	{
		son[u]=0;
		for(int i=0;i<e[u].size();++i)
		{
			int v=e[u][i];
			DP(v);
			son[u]+=son[v];
		}
		/*for(int i=0;i<e[u].size();++i)
		{
			int v=e[u][i];
			r[i]=make_pair(double(son[v])/son[u]*(B[v]+2),i);
		}
		sort(r,r+e[u].size());
		reverse(r,r+e[u].size());*/
		/*for(int i=0;i<e[u].size();++i)
			printf("%.3f %d\n",r[i].first,e[u][r[i].second]);*/
		A[u]=0;
		int sum=0;
		double sumk = 1;
		for(int i=0;i<e[u].size();++i)
		{
/*			int v=e[u][r[i].second];
			A[u]+=(sum+A[v]+1)*double(son[v])/son[u];
			sum+=B[v]+2;*/
			int chose = -1;
			for (int j = 0; j < e[u].size(); ++ j) {
				int v = e[u][j];
				#define calc(x) ((B[(x)] + 2) * (sumk - double(son[(x)])/son[u]))
				#define kk(x) (double(son[(x)])/son[u])
				/*if (!vis[v] && 
				(chose == -1 || (B[chose] + 2) * (sumk - double(son[chose]) / son[u]) >
								(B[v] + 2) * (sumk - double(son[v]) / son[u]) ) )
					chose = v;*/
				if (!vis[v] && (chose == -1 || (calc(chose) > calc(v) || (calc(chose) == calc(v)) && kk(u)>kk(v))))
					chose = v;
				#undef calc
				#undef kk
			}
			vis[chose] = true;
			//cout << u << ' ' << chose << ' ' << (B[chose] + 2) * (sumk - double(son[chose]) / son[u]) << endl;
			
			A[u] += (sum + A[chose] + 1) * double(son[chose]) / son[u];
			
			sum += B[chose] + 2;
			sumk -= double(son[chose]) / son[u];
		}
		if(worm[u])B[u]=0;
		else {
			B[u] = 0;
			for(int i=0;i<e[u].size();++i)
				B[u]+=B[e[u][i]]+2;
		}
	}
	else
	{
		son[u]=1;
		A[u]=0;
		B[u]=0;
	}
	//printf("%d %d %f %f\n",u,son[u],A[u],B[u]);
}
int main()
{
	while(scanf("%d",&n),n)
	{
		memset(vis, 0, sizeof(vis));
		for(int i=1;i<=n;++i)
			e[i].clear();
		for(int i=1;i<=n;++i)
		{
			int x;
			scanf("%d",&x);
			if(x!=-1)
				e[x].push_back(i);
			char ch=' ';
			while(ch!='Y'&&ch!='N')ch=getchar();
			worm[i]=ch=='Y';
		}
		DP(1);
		printf("%.4f\n",A[1]);
	}
	return 0;
}
