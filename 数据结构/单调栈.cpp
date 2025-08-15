#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int main(void) {
    int n; cin >> n;
    stack<i64> s;
    i64 ans = 0;
    for(int i = 0; i < n; i++) {
        int a; cin >> a;
        //维护递减单调栈
        while(s.size() && s.top() <= a) s.pop();
        ans += s.size(); s.push(a);
    }
    cout << ans << endl;
    return 0;
}
