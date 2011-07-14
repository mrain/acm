#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <vector>
using namespace std;

string buff;
string buf[101];
int n, m;
bool g[101][101];
const int SZ = 999973;
vector <int> admire[200010];
vector <int> result[101];

struct hashtable {
	vector <string> s;
	vector <int> next;
	int head[SZ + 1];
	void clear() {
		s.clear(); next.clear();
		memset(head, 0, sizeof(head));
	}
	int find(const string &tmp) {
		int value = 0;
		for (int i = 0; i < (int)tmp.length(); ++ i)
			value = (value * 37 + (tmp[i] - 'a')) % SZ;
		for (int i = head[value]; i; i = next[i])
			if (s[i] == tmp) return i;
		s.push_back(tmp);
		next.push_back(head[value]);
		head[value] = next.size() - 1;
		return next.size() - 1;
	}
}hash;

bool cmp(const int &a, const int &b) {
	return hash.s[a] < hash.s[b];
}

void init() {
	hash.clear();
	for (int i = 0; i < m; ++ i) {
		string w;
		istringstream is(buf[i]);
		is >> w;
		hash.find(w);
	}
	for (int i = 0; i < n + m; ++ i) admire[i].clear();
	for (int i = 0; i < m; ++ i) result[i].clear();
	for (int i = 0; i < m; ++ i) {
		string r;
		istringstream is(buf[i]);
		is >> r;
		while (is >> r) {
			int id = hash.find(r);
			if (id < m) g[id][i] = true;
			else admire[id].push_back(i);
		}
	}
	for (int k = 0; k < m; ++ k)
		for (int i = 0; i < m; ++ i)
			for (int j = 0; j < m; ++ j)
				if (g[i][k] && g[k][j]) g[i][j] = true;
	for (int i = 0; i < n + m; ++ i) {
		for (int j = 0; j < (int)admire[i].size(); ++ j)
			if (admire[i][j] < m)
				for (int k = 0; k < m; ++ k)
					if (k != i && g[admire[i][j]][k])
						admire[i].push_back(k);
		sort(admire[i].begin(), admire[i].end(), cmp);
		admire[i].erase(unique(admire[i].begin(), admire[i].end()), admire[i].end());
		for (int j = 0; j < (int)admire[i].size(); ++ j)
			if (i != admire[i][j])
				result[admire[i][j]].push_back(i);
	}
	for (int i = 0; i < m; ++ i) {
		sort(result[i].begin(), result[i].end(), cmp);
		result[i].erase(unique(result[i].begin(), result[i].end()), result[i].end());
	}
}

int main() {
	int ca = 0;
	while (1) {
		getline(cin, buff);
		istringstream Is(buff);
		Is >> n >> m;
		if (n == 0 && m == 0) break;
		for (int i = 0; i < m; ++ i)
			getline(cin, buf[i]);
		init();
		cout << "--- CASE " << ++ ca << endl;
		for (int i = 0; i < m; ++ i) {
			cout << hash.s[i];
			for (int j = 0; j < (int)result[i].size(); ++ j)
				cout << ' ' << hash.s[result[i][j]];
			cout << endl;
		}
	}
	return 0;
}

