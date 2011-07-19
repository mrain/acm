#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

int N;
char c[11][11];
int s[11];

long long ans;

int getFather(int x) {
    if (s[x] == x) return x;
    return getFather(s[x]);
}

void dfs(int dep, int root) {
    if (dep == N) ++ ans;
    else {
        if (dep == root) dfs(dep + 1, root);
        else {
            for (int k = 0; k < N; ++ k)
                if (c[k][dep] == '1' && getFather(k) != getFather(dep)) {
                    s[dep] = k;
                    dfs(dep + 1, root);
                    s[dep] = dep;
                }
        }
    }
}

int main() {
    while (cin >> N && N) {
        for (int i = 0; i < N; ++ i)
            scanf("%s", c[i]);
        memset(s, -1, sizeof(s));
        ans = 0;
        for (int k = 0; k < N; ++ k) {
            for (int r = 0; r < N; ++ r)
                s[r] = r;
            dfs(0, k);
        }
        cout << ans << endl;
    }
    
    return 0;
}

