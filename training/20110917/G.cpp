#include<queue>
#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>

using namespace std;

#define maxn (55)
#define PB push_back
#define MP make_pair
#define A first
#define B second

typedef pair<int,int> PII;

struct node{
	int v,suffix,nt[26];
};

int cntNode;
node T[1003];

void initTree(){
	cntNode=0;
	memset(T,0,sizeof(T));
}

void addToTree(string r){
	int pos=0;
	for(int i=0;i<r.size();++i){
		int v=r[i]-'a';
		if(T[pos].nt[v]) pos = T[pos].nt[v];
		else {
			T[pos].nt[v] = ++cntNode;
			pos = cntNode;
		}
	}
	++T[pos].v;
}

queue<int> Q;
void constructTree(){
	Q.push(0);
	while(!Q.empty()){
		int x=Q.front();
		T[x].v+=T[T[x].suffix].v;
		Q.pop();
		for(int i=0;i<26;++i)
			if(T[x].nt[i]){
				int y=T[x].nt[i];
				Q.push(y);
				if(x==0)T[y].suffix=0;
				else T[y].suffix=T[T[x].suffix].nt[i];
			}
			else
				T[x].nt[i]=T[T[x].suffix].nt[i];
	}
}

int moveNext(int u,char ch){
	return T[u].nt[ch-'a'];
}

string a[maxn],b[maxn];
int f[maxn][maxn*10][maxn];
vector<PII> g[maxn];
int m,n,l,ans;

void update(int& x, int v) {
	if (x == -1 || x < v) x = v;
	if (v > ans) ans = v;
}

void work() {
	for (int i = 1; i <= m; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) cin >> b[i];
	initTree();
	
	for (int i = 1; i <= m; ++i) {
		g[i].clear();
		
		for (int j = 1; j <= m; ++j) {
			for (int k = 0; k <= a[j].size() && k <= a[i].size(); ++ k) {
				if (i == j && k == a[i].size()) continue;
				bool flag = true;
				for (int t = 0; t < k; ++t)
					if (a[i][a[i].size() - k + t] != a[j][t]) {
						flag = false; break;
					}
				
				if (flag)
					g[i].PB(MP(j, k));
			}
		}
	}

	for (int i = 1; i <= n; ++i) addToTree(b[i]);
	constructTree();
	
	ans = 0;
	memset(f, -1, sizeof(f));
	for (int i = 1; i <= m; ++i) {
		int now = 0, cnt = 0;
		for (int j = 0; j < a[i].size(); ++j) {
			now = moveNext(now, a[i][j]); cnt += T[now].v;
		}
	
		f[a[i].size()][now][i] = cnt;	
		if (cnt > ans) ans = cnt;
	}
	
	//cout << moveNext(0, 'a') << endl;
	
	for (int k = 1; k < l; ++k)
		for (int i = 0; i <= cntNode; ++i)
			for (int j = 1; j <= m; ++j) {
				if (f[k][i][j] == -1) continue;
				//cout << k << ' ' << i << ' ' << j << ' ' << f[k][i][j] << endl;
				
				for (int t = 0; t < g[j].size(); ++t) {
					int to = g[j][t].A, cov = g[j][t].B, now = i, cnt = f[k][i][j];
					
					if (k + a[to].size() - cov > l) continue;
					
					for (int c = cov; c < a[to].size(); ++c) {
						now = moveNext(now, a[to][c]); cnt += T[now].v;
					}
					update(f[k + a[to].size() - cov][now][to], cnt);
				}			
			}
			
	cout << ans << endl ;
}

int main() {
	while (cin >> m >> n >> l) work();

	return 0;
}
