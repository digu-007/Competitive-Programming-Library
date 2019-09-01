void dfs(int s, int p) {
    for (auto &x: g[s]) {
        if (x != p) {
            dfs(x, s);
            dp[x][0] = s;
        }
    }
}

void build(int root) {
    dfs(root, 0);
    for (int j = 1; j < LG; ++j) {
        for (int i = 1; i <= n; ++i) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }
}

int kth(int s, int k) {
    for (int i = LG - 1; i >= 0; --i) {
        if ((1 << i) <= k) {
            s = dp[s][i];
            k -= (1 << i);
        }
    }
    return s;
}
