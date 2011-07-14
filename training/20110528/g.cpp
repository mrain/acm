#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cstring>
#include <map>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>
using namespace std;

//map <string, int> id;
string buf;
int s, f, size;
vector <int> ch[200010];
int dp[200010][2], fs[200010][2], ff[200010][2];
bool notroot[200010];
const int SZ = 999973;

struct hashtable {
	vector <string> s;
	vector <int> next;
	int head[SZ + 1];
	void clear() {
		s.clear(); next.clear();
		memset(head, 0xFF, sizeof(head));
	}
	int find(const string &tmp) {
		int value = 0;
		for (int i = 0; i < (int)tmp.length(); ++ i)
			value = (value * 37 + (tmp[i] - 'a' + 1)) % SZ;
		for (int i = head[value]; i >= 0; i = next[i])
			if (s[i] == tmp) return i;
		s.push_back(tmp);
		next.push_back(head[value]);
		ch[next.size() - 1].clear();
		head[value] = next.size() - 1;
		return next.size() - 1;
	}
}ID;

void init() {
	ID.clear(); size = 0;
	memset(notroot, 0, sizeof(notroot));
	istringstream is(buf);
	is >> s >> f;
	if (s == 0 && f == 0) return;
	while (1) {
		getline(cin, buf);
		if (isdigit(buf[0])) break;
		istringstream is(buf);
		string tmp;
		is >> tmp;
		int father = ID.find(tmp);
		while (is >> tmp) {
			int id = ID.find(tmp);
			notroot[id] = true;
			ch[father].push_back(id);
		}
	}
	size = ID.next.size();
}

void dfs(int u) {
	int ns = 0, nf = 1, a = f;
	for (int i = 0; i < (int)ch[u].size(); ++ i) {
		int v = ch[u][i];
		dfs(v);
		dp[u][0] += dp[v][1]; fs[u][0] += fs[v][1]; ff[u][0] += ff[v][1];
		if (dp[v][0] < dp[v][1] || (dp[v][0] == dp[v][1] && fs[v][0] + ff[v][0] < fs[v][1] + ff[v][1]))
			a += dp[v][0], ns += fs[v][0], nf += ff[v][0];
		else
			a += dp[v][1], ns += fs[v][1], nf += ff[v][1];
	}
	if (a < dp[u][0] + s || (a == dp[u][0] + s && ns + nf < fs[u][0] + ff[u][0] + 1))
		dp[u][1] = a, fs[u][1] = ns, ff[u][1] = nf;
	else {
		dp[u][1] = dp[u][0] + s;
		fs[u][1] = fs[u][0] + 1;
		ff[u][1] = ff[u][0];
	}
}

int main() {
	int ca = 0;
	getline(cin, buf);
	while (1) {
		init();
		if (s == 0 && f == 0) break;
		int ans = 0, ns = 0, nf = 0;
		memset(dp, 0, sizeof(dp));
		memset(fs, 0, sizeof(fs));
		memset(ff, 0, sizeof(ff));
		for (int i = 0; i < size; ++ i)
			if (notroot[i] == false) {
				dfs(i);
				ans += dp[i][1];
				ns += fs[i][1];
				nf += ff[i][1];
			}
		printf("%d. %d %d %d\n", ++ ca, ns, nf, ans);
	}
	return 0;
}

