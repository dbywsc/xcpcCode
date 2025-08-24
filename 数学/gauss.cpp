/*
    0 无解
    1 唯一解
    2 多解
*/
int gauss(std::vector<std::vector<double>> a, std::vector<double>& ans) {
    const double EPS = 1e-9;
    int n = (int)a.size();
    if(n == 0) return 1;
    int m = (int)a[0].size() - 1;
    std::vector<int> where(m, -1);
    int row = 0;
    for(int col = 0; col < m && row < n; col++) {
        int sel = row;
        for(int i = row; i < n; i++) {
            if(fabs(a[i][col]) > fabs(a[sel][col])) sel = i;
        }
        if(fabs(a[sel][col]) < EPS) continue;
        std::swap(a[sel], a[row]);
        double inv_pivot = 1.0 / a[row][col];
        for(int j = col; j <= m; j++) 
            a[row][j] *= inv_pivot;
        for(int i = 0; i < n; i++) {
            if(i != row && fabs(a[i][col]) > EPS) {
                double factor = a[i][col];
                for(int j = col; j <= m; j++) 
                    a[i][j] -= factor * a[row][j];
            }
        }
        where[col] = row;
        ++row;
    }
    ans.assign(m, 0.0);
    for(int i = 0; i < m; i++) {
        if(where[i] != -1) ans[i] = a[where[i]][m];
    }
    for(int i = 0; i < n; i++) {
        bool all_zero = true;
        for(int j = 0; j < m; j++) {
            if(fabs(a[i][j]) > EPS) {
                all_zero = false;
                break;
            }
        }
        if(all_zero && fabs(a[i][m]) > EPS) return 0;
    }
    for(int i = 0; i < m; i++) if(where[i] == -1) return 2;
    return 1;
}