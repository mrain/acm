#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (700)
#define PB push_back

int n, p;

inline void update(int& x, int v) {
	if (x == -1 || x > v) x = v;
}

inline int abs(int x) {
	return x < 0 ? -x : x;
}

struct point {
	int x, y;
	
	point() {}
	point(const int& a, const int& b) : x(a), y(b) {}
	
	inline point operator - (const point& a) {
		return point(x - a.x, y - a.y);
	}
};

inline int cross(point a, point b) {
	return a.x * b.y - a.y * b.x;
}

inline int value(const point& a, const point& b) {
	return abs(a.x + b.x) * abs(a.y + b.y) % p;
}

inline bool operator < (const point& a, const point& b) {
	return a.x < b.x;
}

int f[maxn][maxn];

bool convex(vector<point>& a, vector<point>& g) {
	g.clear();
	vector<point> stack;
	
	sort(a.begin(), a.end()); 
	
	stack.clear(); stack.PB(a[0]);
	for (int i = 1; i < a.size(); ++i) {
		while (stack.size() >= 2 && cross(stack[stack.size() - 1] - stack[stack.size() - 2], a[i] - stack[stack.size() - 1]) <= 0) stack.pop_back();
		stack.PB(a[i]);
	}
	
	for (int i = 0; i < stack.size() - 1; ++i) g.PB(stack[i]);
	
	stack.clear(); stack.PB(a[0]);
	for (int i = 1; i < a.size(); ++i) {
		while (stack.size() >= 2 && cross(stack[stack.size() - 1] - stack[stack.size() - 2], a[i] - stack[stack.size() - 1]) >= 0) stack.pop_back();
		stack.PB(a[i]);
	}
	
	for (int i = stack.size() - 1; i > 0; --i) g.PB(stack[i]);
	
	//for (int i = 0; i < g.size(); ++i) printf("(%d, %d)\n", g[i].x, g[i].y);
	
	return a.size() == g.size();
}

void work() {
	vector<point> a, g;
	a.clear();
	
	for (int i = 0; i < n; ++i) {
		int x, y; scanf("%d%d", &x, &y);
		a.PB(point(x, y));
	}
	
	if (!convex(a, g)) {
		puts("I can't cut."); return ;
	}
	
	if (n <= 3) {
		puts("0"); return ;
	}
	
	for (int i = 0; i < n; ++i) g.PB(g[i]);
	for (int i = 0; i < n + n - 1; ++i) f[i][1] = 0;
	
	for (int k = 2; k < n - 1; ++k) {
		for (int i = 0; i < n + n - k; ++i) {
			f[i][k] = -1; int x = value(g[i], g[i + k]);
			for (int j = 1; j <= k - 1; ++j) update(f[i][k], f[i][j] + f[i + j][k - j]);
			f[i][k] += x;
		}
	}
	
	int ans = -1;
	for (int i = 0; i < n; ++i) update(ans, f[i][n - 2]);
	printf("%d\n", ans);
}

int main() {
	int cases = 0;

	while (scanf("%d%d", &n, &p) == 2) {
		if (cases++) puts("");
	
		work();	
	}

	return 0;
}

/*
Input

There're multiple cases. There's a blank line between two cases. The first line of each case contains two integers, N and p (3 ≤ N, p ≤ 300), indicating the number of vertices. Each line of the following N lines contains two integers, x and y (-10000 ≤ x, y ≤ 10000), indicating the coordinate of a vertex. You have known that no two vertices are in the same coordinate.
Output

If the cake is not convex polygon-shaped, output "I can't cut.". Otherwise, output the minimum cost.
Sample Input

3 3
0 0
1 1
0 2

Sample Output

0
*/
