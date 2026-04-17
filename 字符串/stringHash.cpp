constexpr unsigned long long BASE = 131313;

unsigned long long getHash(std::string s) {
    unsigned long long ans = 0;
    for (int i = 0; i < s.length(); i++) {
        ans = ans * BASE + s[i];
    }
    return ans;
}
