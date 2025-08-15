#include <bits/stdc++.h>
#define endl '\n'
using i64 = long long;
int main(void) {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
    std::string s1, s2;
    std::cin >> s1 >> s2;
    int len1 = s1.size(), len2 = s2.size();
    std::vector<int> ne(len2);
    int j = 0;
    for(int i = 1; i < len2; i++) {
        while(j > 0 && s2[i] != s2[j]) {
            j = ne[j - 1];
        }
        if(s2[j] == s2[i]) j++;
        ne[i] = j;
    }
    j = 0;
    for(int i = 0; i < len1; i++) {
        while(j > 0 && s1[i] != s2[j]) j = ne[j - 1];
        if(s2[j] == s1[i]) j++;
        if(j == len2) {
            std::cout << i + 1 - len2 + 1 << endl;
            j = ne[j - 1];
        }
    }
    for(auto i : ne) std::cout << i << " ";
    return 0;
}
