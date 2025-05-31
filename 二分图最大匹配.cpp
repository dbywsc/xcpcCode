#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n1, n2, m;
vector<int> G[N];
int match[N];
bool st[N];
bool find(int u) {
    for(auto v : G[u]) {
        if(!st[v]) {
            st[v] = 1;
            if(match[v] == 0 || find(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}
int main(void) {
    cin >> n1 >> n2 >> m;
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
    }
    int res = 0;
    for(int i = 1; i <= n1; i++) {
        memset(st, 0, sizeof(st));
        if(find(i)) res++;
    }
    cout << res << endl;
    return 0;
}
