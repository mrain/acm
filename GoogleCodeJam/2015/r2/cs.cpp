#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

int tests, n;
map <string, int> id;
vector<string> line;
vector <int> sentences[210];
set <int> eng, french, tmpeng, tmpfr, vv;
bool vis[10000];

int getid(string word) {
	if (id.count(word) == 0) {
		int p = id.size();
		id[word] = p;
		return p;
	} else return id[word];
}

void input() {
	line.clear();
	/*char c = getchar();
	while (c != '\n') c = getchar();*/

	string tmp = "";
	char c = getchar();
	while (c != '\n' && c != EOF) {
		if (c == ' ') {
			line.push_back(tmp);
			tmp = "";
		} else tmp += c;
		c = getchar();
	}
	line.push_back(tmp);
}


int main() {
	scanf("%d", &tests);
	for (int T = 1; T <= tests; ++ T) {
		id.clear(); eng.clear(); french.clear();
		scanf("%d", &n);

int base = 0;
		memset(vis, 0, sizeof(vis));
		char c = getchar();
		while (c != '\n') c = getchar();

		memset(vis, 0, sizeof(vis));
		input();
		for (string word : line) {
			//cout << word << endl;
			eng.insert(getid(word));
		}

		input();
		for (string word : line) {
			//cout << word << endl;
			int i = getid(word);
			if (eng.count(i) != 0) {
				//cout << word << ' ' << i << endl;
				++ base;
				vis[i] = true;
			}
			french.insert(i);
		}

		for (int k = 0; k < n - 2; ++ k) {
			input();
			sentences[k].clear();
			int l = line.size();
			for (int i = 0; i < l; ++ i) {
				int a = getid(line[i]);
				if (!vis[a]) sentences[k].push_back(a);
			}
		}

		int m = n - 2;
		int ans = 66666666;
		for (int mask = 0; mask < (1 << m); ++ mask) {
			int cur = 0;
			tmpeng.clear();
			tmpfr.clear();
			vv.clear();
			for (int k = 0; k < m; ++ k) {
				if (mask & (1 << k)) {
					for (int i = 0; i < sentences[k].size(); ++ i) {
						int word = sentences[k][i];
						if (vis[word] || vv.count(word) != 0) continue;
						if (eng.count(word) != 0 || tmpeng.count(word) != 0) {
							++ cur;
				if (cur >= ans) break;
							vv.insert(word);
						}
						if (french.count(word) == 0) tmpfr.insert(word);
					}
				} else {
					for (int i = 0; i < sentences[k].size(); ++ i) {
						int word = sentences[k][i];
						if (vis[word] || vv.count(word) != 0) continue;
						//cout << word << '!' << french.count(word) << ' ' << tmpfr.count(word) << endl;
						if (french.count(word) != 0 || tmpfr.count(word) != 0) {
							++ cur;
				if (cur >= ans) break;
							vv.insert(word);
						}
						if (eng.count(word) == 0) tmpeng.insert(word);
					}
				}
				if (cur >= ans) break;
			}
			//cout << mask << ' ' << cur << ' ' << base << endl;
			ans = min(ans, cur);
		}
		printf("Case #%d: %d\n", T, ans + base);

	}
    return 0;
}
