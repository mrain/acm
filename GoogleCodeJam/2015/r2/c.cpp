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
vector <int> eng, french;
vector <int> e[10000], w[10000];
bool vis[10000];
int me, mf;

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

		char c = getchar();
		while (c != '\n') c = getchar();

		input();
		for (string word : line) {
			//cout << word << endl;
			eng.insert(getid(word));
		}
		input();
		for (string word : line) {
			//cout << word << endl;
			french.insert(getid(word));
		}

		memset(vis, 0, sizeof(vis));
		for (int k = 0; k < n - 2; ++ k) {
			input();

			int l = line.size();
			for (int i = 0; i < l; ++ i) {
				int a = getid(line[i]);
				sentences[k].push_back(i);
			}
		}
		printf("Case #%d: %d\n", T, ans);

	}
    return 0;
}
