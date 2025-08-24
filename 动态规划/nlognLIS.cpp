#include <bits/stdc++.h>
#define x first
#define y second
using i64 = long long;
typedef std::pair<int, int> PII;
int main(void) {
    int n; std::cin >> n;
    std::vector<int> a(n);
    std::vector<int> f;
    for(int i = 0; i < n; i++) std::cin >> a[i];
    for(int i = 0; i < n; i++) {
        auto it = std::lower_bound(f.begin(), f.end(), a[i]);
        if(it == f.end()) f.push_back(a[i]);
        else *it = a[i];
    }
    std::cout << f.size();
    return 0;
}
