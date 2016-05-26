#include <iostream>
#include <set>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;

set <int> cur;
map <int, int> pos;
int n, depth[100010], a[100010];

int main() {
    cur.clear(); pos.clear();
    memset(depth, 0, sizeof(depth));
    cin >> n;
    cin >> a[0];
    cur.insert(a[0]);
    pos[a[0]] = 0;
    for (int i = 1; i < n; ++ i) {
        if (i != 1) cout << ' ';
        cin >> a[i];
        set<int>::iterator it = cur.lower_bound(a[i]);
        if (it == cur.begin()) {
            int k = *it, pk = pos[k];
            depth[i] = depth[pk] + 1;
            cout << k;
        } else {
            set<int>::iterator its = cur.lower_bound(a[i]);
            its --;
            if (it == cur.end()) {
                int k = *its, pk = pos[k];
                depth[i] = depth[pk] + 1;
                cout << k;
            } else {
                int k = *it, pk = pos[k];
                int j = *its, pj = pos[j];
                if (depth[pk] < depth[pj]) {
                    k = j;
                    pk = pj;
                }
                depth[i] = depth[pk] + 1;
                cout << k;
            }
        }
        cur.insert(a[i]);
        pos[a[i]] = i;
    }
    cout << endl;
    return 0;
}
