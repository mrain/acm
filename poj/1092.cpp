#include <cstdio>
#include <map>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>
#define Eps 1e-12
using namespace std;

inline int sgn(double a) {
	return a < -Eps ? -1 : a > Eps ? 1 : 0;
}

struct Point {
	double x, y;
	Point(double x = 0, double y = 0): x(x), y(y) {}
	Point operator +(const Point &t) const { return Point(x + t.x, y + t.y); }
	Point operator -(const Point &t) const { return Point(x - t.x, y - t.y); }
	Point operator *(const double &t) const { return Point(x * t, y * t); }
	Point operator /(const double &t) const { return Point(x / t, y / t); }
	double cross(const Point &t) { return x * t.y - y * t.x; }
	double dot(const Point &t) { return x * t.x + y * t.y; }
	double norm() { return x * x + y * y; }
	double abs() { return sqrt(norm()); }
	double arg() { return atan2(x, y); }
};

ostream &operator <<(ostream &os, const Point &t) {
	os << '(' << t.x << ", " << t.y << ')';
	return os;
}

istream &operator >>(istream &is, const Point &t) {
	return is >> t.x >> t.y;
}

ostream &operator <<(ostream &os, const vector<int> l) {
	os << '(';
	for (int i = 0; i < (int)l.size(); ++ i)
		os << (i > 0 ? ", " : "") << l[i];
	os << ')';
	return os;
}

int tests, n, cnt, size;
vector <int> e[210], oppo[210], polygon;
Point p[210];
Point comparator;
Point faraway = Point(90127, 99971);
int vis[210][210];
bool finish[210][210];
map <vector<int>, bool> has;

bool cmp_arg(const int &a, const int &b) {
	return sgn((p[a] - comparator).arg() - (p[b] - comparator).arg()) == -1;
}

void deal_list(int i) {
	comparator = p[i];
	sort(e[i].begin(), e[i].end(), cmp_arg);
}

bool intersect(Point a, Point b, Point c, Point d) {
	int t1 = sgn((c - a).cross(b - a));
	int t2 = sgn((d - a).cross(b - a));
	if (t1 * t2 > 0) return false;
	t1 = sgn((a - c).cross(d - c));
	t2 = sgn((b - c).cross(d - c));
	return t1 * t2 <= 0;
}

bool check() {
	int cnt, m = polygon.size();
	vector <int> tmp;
	for (int i = 0; i < n; ++ i) {
		cnt = 0;
		for (int j = 0; j < m; ++ j)
			if (polygon[j] == i) ++ cnt;
		tmp.push_back(cnt);
	}
	if (has.count(tmp)) return false;
	else has[tmp] = true;
	polygon.push_back(polygon[0]);
	for (int i = 0; i < n; ++ i) {
		bool flag = true;
		for (int j = 0; j < m; ++ j)
			if (i == polygon[j]) {
				flag = false;
				break;
			}
		if (!flag) continue;
		cnt = 0;
		for (int j = 0; j < m; ++ j)
			if (intersect(p[i], faraway, p[polygon[j]], p[polygon[j + 1]]))
				++ cnt;
		if (cnt & 1) {
			cout << i << endl;
			return false;
		}
	}
	return true;
}

void walk(int now, int t) {
	if (e[now].size() <= 1) return;
	finish[now][t] = true;
	memset(vis, 0xFF, sizeof(vis));
	vis[now][t] = 0;
	int x = e[now][t], y = (oppo[now][t] + 1) % (oppo[x].size());
	while (!finish[x][y]) {
		if (e[x].size() <= 1) return;
		vis[x][y] = vis[now][t] + 1;
		finish[x][y] = true;
		now = x; t = y;
		x = e[now][t]; y = (oppo[now][t] + 1) % (oppo[x].size());
	}
	if (vis[x][y] >= 0 && (vis[now][t] - vis[x][y] + 1) == size) {
		polygon.clear();
		now = x, t = y; vis[now][t] = -1;
		polygon.push_back(now);
		x = e[now][t]; y = (oppo[now][t] + 1) % (oppo[x].size());
		while (vis[x][y] >= 0) {
			polygon.push_back(x);
			now = x; t = y;
			x = e[now][t]; y = (oppo[now][t] + 1) % (oppo[x].size());
		}
//		cout << polygon << endl;
		if (check()) ++ cnt;
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &tests);
	while (tests --) {
		cnt = 0;
		has.clear();
		memset(finish, 0, sizeof(finish));
		for (int i = 0; i < n; ++ i) {
			e[i].clear();
			oppo[i].clear();
		}
		scanf("%d", &n);
		for (int step = 0; step < n; ++ step) {
			int i, k, t;
			scanf("%d", &i); -- i;
			scanf("%lf%lf", &p[i].x, &p[i].y);
			scanf("%d", &k);
			for (int j = 0; j < k; ++ j) {
				scanf("%d", &t); -- t;
				e[i].push_back(t);
			}
		}
		for (int i = 0; i < n; ++ i) deal_list(i);
		scanf("%d", &size);// size *= 2;
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < (int)e[i].size(); ++ j) {
				int v = e[i][j];
				for (int k = 0; k < (int)e[v].size(); ++ k)
					if (e[v][k] == i)
						oppo[i].push_back(k);
			}
		}
		memset(vis, -1, sizeof(vis));
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < (int)e[i].size(); ++ j)
				if (!finish[i][j]) {
					walk(i, j);
				}
		cout << cnt << endl;
	}
	return 0;
}
