#include <bits/stdc++.h>
#define int long long
using namespace std;
int exgcd(int a, int b, int &x, int &y) {
    if(!b) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
signed main(void) {
    int n; cin >> n;
    while(n--) {
        int a, b, m;
        cin >> a >> b >> m;
        int x, y;
        int d = exgcd(a, m, x, y);
        if(b % d) cout << "impossible" << endl;
        else cout << x * (b / d) % m << endl;
    }
    return 0;
