#include <cstdio>
#include <cstring> 
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define maxn (2120)

struct point {
	int x,y;
	int init(){
		return scanf("%d%d",&x,&y);
	}
};

inline bool operator<(const point& a,const point& b) {
	return a.x<b.x||a.x==b.x&&a.y<b.y;
} 

inline bool operator==(const point& a,const point& b) {
	return a.x==b.x&&a.y==b.y;
} 

inline long long xmult(const point& a,const point& b,const point& c) {
	return ((long long)(a.x-c.x)*(long long)(b.y-c.y))-((long long)(a.y-c.y)*(long long)(b.x-c.x));
}

void calc(vector<point>& g){
	vector<point> stack,f; stack.clear(),f.clear();
	
	int n=g.size();
	sort(g.begin(),g.end());
	
	stack.push_back(g[0]);
	for (int i=1;i<n;i++) {
		while (stack.size()>1&&xmult(g[i],stack[stack.size()-1],stack[stack.size()-2])<=0ll) stack.pop_back();
		
		stack.push_back(g[i]);
	}	
	for (int i=1;i<stack.size();i++)
		f.push_back(stack[i]);
	
	stack.clear();
	
	stack.push_back(g[0]);
	for (int i=1;i<n;i++) {
		while (stack.size()>1&&xmult(g[i],stack[stack.size()-1],stack[stack.size()-2])>=0ll) stack.pop_back();
		
		stack.push_back(g[i]);
	}
	for (int i=stack.size()-2;i>=0;i--)
		f.push_back(stack[i]);
		
	stack.clear();
	sort(f.begin(),f.end());
	
	for (int i=0;i<n;i++) if (!(*lower_bound(f.begin(),f.end(),g[i])==g[i])) stack.push_back(g[i]);
	
	g.clear();
	for (int i=0;i<stack.size();i++)
		g.push_back(stack[i]);
/*		
	puts("F==================================");
	for (int i=0;i<f.size();i++) printf("(%d,%d)",f[i].x,f[i].y); puts("");
	puts("G==================================");
	for (int i=0;i<g.size();i++) printf("(%d,%d)",g[i].x,g[i].y); puts("");
*/
}

int main() {
	int n;
	
	vector<point> g;
	
	while (scanf("%d",&n)==1) {
		point tmp; g.clear();
		for (int i=0;i<n;i++) {
			tmp.init(); g.push_back(tmp);
		}	
		
		int ans=0;
		while (g.size()>=3) calc(g),ans++;
		
		printf("%d\n",ans);
	}

	return 0;
}
