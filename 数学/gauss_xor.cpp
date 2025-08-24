/*
    0 无解
    1 唯一解
    2 多解
*/
int gauss(std::vector<std::vector<int>> a, std::vector<int>& ans) {
    int n = (int)a.size();
    if(n == 0) return 1;
    int m = (int)a[0].size() - 1;
    std::vector<int> where(m, -1);
    int row = 0;
    for(int col = 0; col < m && row < n; col++) {
        int sel = row;
        while(sel < n && a[sel][col] == 0) sel++;
        if(sel == n) continue;
        std::swap(a[sel], a[row]);
        where[col] = row;
        for(int i = 0; i < n; i++) {
            if(i != row && a[i][col]) {
                for(int j = col; j <= m; j++) a[i][j] ^= a[row][j];
            }
        }
        row++;
    }
    ans.assign(m, 0);
    for(int i = 0; i < m; i++) {
        if(where[i] != -1) ans[i] = a[where[i]][m];
    }
    for(int i = 0; i < n; i++) {
        bool all_zero = true;
        for(int j = 0; j < m; j++) {
            if(a[i][j]) {
                all_zero = false;
                break;
            }
        }
        if(all_zero && a[i][m]) return 0;
    }
    for(int i = 0; i < m; i++) if(where[i] == -1) return 2;
    return 1;
}