#include <cstdio>
#include <sstream>
#include <queue>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <cstring>
#include <algorithm>
#define ERROR 0x3F3F3F3F
using namespace std;

int n, m, s, t;
vector <int> l[51][1010];
vector <int> w[51], e[51];
int dist[51];
bool inq[51];
queue <int> q;
char buf[20000];

int walk(int u, int k, int start) {
    int i;
    for (i = 1; i < (int)l[u][k].size(); i += 2)
        if (l[u][k][i] >= start) break;
    -- i;
    int s = max(l[u][k][i], start);
    while (i + 1 < (int)l[u][k].size() && s + w[u][k] > l[u][k][i + 1]) {
        i += 2;
        if (i >= (int)l[u][k].size()) return ERROR;
        s = l[u][k][i];
    }
    return s + w[u][k];
}

int main() {
	freopen("1613.in", "r", stdin);
    while (gets(buf), sscanf(buf, "%d%d%d%d", &n, &m, &s, &t) == 4 && n != 0) {
        -- s, -- t;
        memset(dist, 0x3F, sizeof(dist));
        memset(inq, 0, sizeof(inq));
        for (int i = 0; i < n; ++ i)
            for (int j = 0; j < 1000; ++ j)
                l[i][j].clear();
        for (int i = 0; i < n; ++ i) {
            e[i].clear();
            w[i].clear();
        }
        for (int i = 0; i < m; ++ i) {
            gets(buf);
            istringstream is(buf);
            int a, b, tmp, ta, tb;
            is >> a >> b >> tmp;
            if (a == b) continue;
            -- a; -- b;
            ta = e[a].size(); tb = e[b].size();
            e[a].push_back(b);
            w[a].push_back(tmp);
            e[b].push_back(a);
            w[b].push_back(tmp);
            l[a][ta].push_back(0);
            l[b][tb].push_back(0);
            while (is >> tmp) {
                l[a][ta].push_back(tmp);
                l[b][tb].push_back(tmp);
            }
        }
        while (!q.empty()) q.pop();
        q.push(s);
        dist[s] = 0; inq[s] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = 0; i < (int)e[u].size(); ++ i) {
                int v = e[u][i];
                    int p = walk(u, i, dist[u]);
                    if (dist[v] > p) {
                        dist[v] = p;
                        if (!inq[v]) {
                            q.push(v);
                            inq[v] = true;
                        }
                    }
            }
            inq[u] = false;
        }
        /*for (int i = 0; i < n; ++ i)
            cout << dist[i] << ' ';
        cout << endl;*/
        if (dist[t] == ERROR) puts("*");
        else printf("%d\n", dist[t]);
    }
    return 0;
}
