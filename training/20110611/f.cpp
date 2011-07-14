#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <bitset>
using namespace std;

string buf;
int n, m, root;
map <string, int> id;
vector <int> need[101];
int g[101], stand[100010];
bitset <100> p[100];
bool reach[100010];

inline int getid(const string &a) {
	if (!id.count(a)) {
		id.insert(make_pair(a, id.size()));
		return id.size() - 1;
	} else {
		return id[a];
	}
}

bool init() {
	id.clear();
	getline(cin, buf);
	sscanf(buf.c_str(), "%d%d", &n, &m);
	if (n + m == 0) return false;
	for (int i = 0; i < n; ++ i) {
		getline(cin, buf);
		getid(buf);
	}
	for (int i = 0; i < m; ++ i) {
		getline(cin, buf);
		need[i].clear();
		int l = (int)buf.length(), pre = 0;
		for (int j = 0; j < l; ++ j)
			if (buf[j] == ',' || buf[j] == ':') {
				need[i].push_back(getid(string(buf.begin() + pre, buf.begin() + j)));
				pre = j + 2;
				if (buf[j] == ':') {
					g[i] = getid(string(buf.begin() + pre, buf.end()));
					stand[g[i]] = i;
					break;
				}
			}
	}
	root = getid("Sorcerer's Stone");
	return true;
}

bool can(const vector <int> &l) {
	for (int i = 0; i < (int)l.size(); ++ i)
		if (!reach[l[i]]) return false;
	return true;
}

bool work(int k) {
	int h = g[k];
	vector <int> &l = need[k];
	p[k].reset();
	for (int i = 0; i < (int)l.size(); ++ i)
		if (!reach[l[i]]) return false;
		else if (l[i] >= n) p[k] |= p[stand[l[i]]];
	reach[h] = true;
	p[k].set(k);
	return true;
}

int main() {
	while (1) {
		memset(stand, -1, sizeof(stand));
		if (!init()) break;
		memset(reach, 0, sizeof(reach));
		for (int i = 0; i < n; ++ i) reach[i] = 1;
		while (1) {
			bool flag = false;
			for (int i = 0; i < m; ++ i)
				if (!reach[g[i]])
					flag |= work(i);
			if (!flag) break;
		}
		if (stand[root] == -1 || !reach[root]) cout << "-1" << endl;
		else cout << int(p[stand[root]].count()) << endl;
	}
	return 0;
}

