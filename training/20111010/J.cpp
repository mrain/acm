#include<cstdio>
#include<cstring>
#include<algorithm>
#include <iostream>
#include <vector>
#include <cctype>
#include <string>
using namespace std;


//start suffix array
#define M 400003
int rank[M],sa[M],X[M],Y[M],buc[M],init[M];
bool cmp(int *r,int a,int b,int l){
	return r[a]==r[b]&&r[a+l]==r[b+l];
}
void suffix(int n,int m=256){
	/*int i,l,p,*x=X,*y=Y;
	for(i=0;i<m;++i)buc[i]=0;
	for(i=0;i<n;++i)buc[x[i]=init[i]]++;
	for(i=1;i<m;++i)buc[i]+=buc[i-1];
	for(i=n-1;i>=0;--i)sa[--buc[x[i]]]=i;
	for(l=1,p=1;p<n;m=p,l*=2){
		p=0;
		for(i=n-1;i<n;++i)y[p++]=i;
		for(i=0;i<n;++i)if(sa[i]>=l)y[p++]=sa[i]-l;
		for(i=0;i<m;++i)buc[i]=0;
		for(i=0;i<n;++i)buc[x[y[i]]]++;
		for(i=1;i<m;++i)buc[i]+=buc[i-1];
		for(i=n-1;i>=0;--i)sa[--buc[x[y[i]]]]=y[i];
		for(swap(x,y),x[sa[0]]=0,i=1,p=1;i<n;++i)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],l)?p-1:p++;
		cout << p << ' ' << l << endl;
	}*/
	register int i,l,p,*x=X,*y=Y;
	for(i=0;i<m;++i)buc[i]=0;
	for(i=0;i<n;++i)buc[x[i]=init[i]]++;
	for(i=1;i<m;++i)buc[i]+=buc[i-1];
	for(i=n-1;i>=0;--i)sa[--buc[x[i]]]=i;
	for(l=1,p=1;p<n;m=p,l*=2){
		p=0;
		for(i=n-l;i<n;++i)y[p++]=i;
		for(i=0;i<n;++i)if(sa[i]>=l)y[p++]=sa[i]-l;
		for(i=0;i<m;++i)buc[i]=0;
		for(i=0;i<n;++i)buc[x[y[i]]]++;
		for(i=1;i<m;++i)buc[i]+=buc[i-1];
		for(i=n-1;i>=0;--i)sa[--buc[x[y[i]]]]=y[i];
		for(swap(x,y),x[sa[0]]=0,i=1,p=1;i<n;++i)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],l)?p-1:p++;
	}
//	for(i=1;i<n;++i)
//		rank[sa[i]]=i;
} 
void initS(int *r,int n){
	for(int i=0;i<n;++i)init[i]=r[i];
	init[n]=0;
	suffix(n+1);
	/*for(int i=1;i<=n;++i)
		printf("%d\n",sa[i]);*/
}
//suffix array end

//calculate

long long sum[M];
int G[M];

inline char d2c(int x) {
	if (x < 11) return x + '0' - 1;
	if (x < 37) return x - 11 + 'A';
	return x - 37 + 'a';
}

inline int c2d(char x) {
	if (isdigit(x)) return x - '0' + 1;
	if (isupper(x)) return 11 + x - 'A';
	return 37 + x - 'a';
}

inline long long calc(int L, int R, int pos, int now) {
	int l = L, r = R, t = L - 1;
	while (l <= r) {
		int mid = (l + r) / 2; 
		if (G[sa[mid] + pos] <= now) t = mid, l = mid + 1;
		else r = mid - 1;
	}
//	cout << '!' <<  L << ' ' << R << ' ' << pos << ' ' << now << ' ' << sum[t] - sum[L - 1] - ((long long) pos * (long long) (t - L + 1)) << endl;
	return sum[t] - sum[L - 1] - ((long long) pos * (long long) (t - L + 1));
}

void work(int n, long long m) {
	vector<int> ans;
	for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + (long long) (n - sa[i]);// cout << sum[i] << endl;
	
	int L = 1, R = n;
	for (int i = 0; i < n; ++i) {
		if (i != 0) {
			m -= (long long) (R - L + 1);
			if (m <= 0) break;
		}
		//cout << m << endl;
		
		int l = 1, r = 62, now = 0; long long opt = 0;
		while (l <= r) {
			int mid = (l + r) / 2; long long num = calc(L, R, i, mid);
			
			if (num < m) l = mid + 1, opt = num, now = mid;
			else r = mid - 1;
		}
		
		ans.push_back(now + 1), m -= opt;
		
		while (L <= n && G[sa[L] + i] <= now) L++;
		while (R > 0 && G[sa[R] + i] > now + 1) R--;
		
		//cout << now << ' ' << m << ' ' << opt << ' ' << L << ' ' << R << endl;
	}
	
	for (int i = 0; i < ans.size(); ++i) putchar(d2c(ans[i]));
	puts("");
}

//calculate
char buf[110000];

int main(){
	int T; scanf("%d", &T);
	
	int n; long long m;
	
	for (int t = 1; t <= T; ++t) {
		printf("Case %d: ", t);
		
//		scanf("%d", &n);
//		scanf("%s", buf); 
		//memset(buf, 0, sizeof(buf));
		cin >> buf >> m;
		n = strlen(buf);
//		cout << ((long long)n * (n + 1)) / 2 << endl;
//		cout << buf << endl;
		memset(G, 0, sizeof(G));
		for (int i = 0; i < n; ++i) G[i] = c2d(buf[i]);
//		continue;
		initS(G, n);
//		continue;
		work(n, m);
	}
	
	return 0;
}
