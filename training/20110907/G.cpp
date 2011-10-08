#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <set>

using namespace std;

#define maxn (1000)

int gcd(int a, int b) {
return b == 0 ? a : gcd(b, a %b);
}

struct point {
	int x, y;
	
	point(){}
	point(int a, int b) : x(a), y(b) {}
	
	void init() {
		string a, b;
		cin >> a >> b;
		
		x = y = 0;
		
		bool flag, sgn; int cnt;
		
		flag = false, cnt = 0;
		if (a[0] == '-') sgn = true;
		else sgn = false;
		for (int i = sgn ? 1 : 0 ; i < a.size(); ++i) {
			if (a[i] == '.') {
				flag = true; continue;
			}
			
			if (flag) cnt++;
			x = x * 10 + a[i] - '0';
		}
		for (int i = cnt; i < 4; ++i) x *= 10;
		if (sgn) x = -x;
		
		flag = false, cnt = 0;
		if (b[0] == '-') sgn = true;
		else sgn = false;
		for (int i = sgn ? 1 : 0 ; i < b.size(); ++i) {
			if (b[i] == '.') {
				flag = true; continue;
			}
			
			if (flag) cnt++;
			y = y * 10 + b[i] - '0';
		}
		for (int i = cnt; i < 4; ++i) y *= 10;
		if (sgn) y = -y;
	}
};

struct line {
	point a, b;
} g[maxn];

int mark[300000];
int a[maxn], b[maxn], step[maxn];
int n, ans;

struct egg {
	int sum;
	
	int size() {
		return sum;
	}
	
	void init() {
		memset(mark, 0, sizeof(mark));
	}
	
	void clear() {
		sum = 0;
	}
	
	void insert(int x, int y) {
		x = x / 10000 + 10001, y = y / 10000 + 10001;
		
		if (mark[y] != x) mark[y] =  x, sum++;
	}
} f;

void work() {
	for (int i = 1; i <= n; ++i) if (g[i].a.x > g[i].b.x) swap(g[i].a, g[i].b); 
	for (int i = 1; i <= n; ++i) step[i] = gcd(abs(g[i].b.x - g[i].a.x), abs(g[i].b.y - g[i].a.y));
	for (int i = 1; i <= n; ++i) {
		if (step[i] != 0) a[i] = (g[i].b.x - g[i].a.x) / step[i], b[i] = (g[i].b.y - g[i].a.y) / step[i];
		else a[i] = b[i] = 0;
	}
	
	for (int X = -100000000; X <= 100000000; X += 10000) {
		f.clear();
	
		for (int i = 1; i <= n; ++i) {
			if (X < g[i].a.x || X > g[i].b.x) continue;
			
			if (X == g[i].a.x && X == g[i].b.x) {
				if (g[i].a.y == g[i].b.y) {
					if (g[i].a.y % 10000 == 0) f.insert(X, g[i].a.y);
					continue;
				}
			
				if (g[i].a.y > g[i].b.y) swap(g[i].a, g[i].b);
			
				int st = g[i].a.y / 10000 * 10000, ed = g[i].b.y / 10000 * 10000;	
				
				for (int Y = st; Y <= ed; Y += 10000) {
					int B = Y - g[i].a.y;
					if (B % b[i] != 0) continue;
					
					f.insert(X, Y);
				}	
				
				continue;
			}
			
			if (g[i].a.x == g[i].b.x) continue;
			
			int A = X - g[i].a.x;
			if (A % a[i] != 0) continue;
			int B = b[i] * (A / a[i]);
			int Y = g[i].a.y + B;
			if (Y % 10000 != 0) continue;
			
			f.insert(X, Y);
		}
		
		ans += f.size();
	}
}

int main() {
	//printf("%d\n", gcd(0, 0));

	int T; scanf("%d", &T);
	
	for (int t = 1; t <= T; ++t) {
		printf("Case %d: ", t);
		
		//puts("");
	
		scanf("%d", &n);
		
		for (int i = 1; i <= n; ++i) g[i].a.init(), g[i].b.init();
		
		ans = 0, f.init();
		work();
		
		printf("%d\n", ans);
	}

	return 0;
}
