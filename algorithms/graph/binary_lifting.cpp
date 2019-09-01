int lca(int u, int v) {
    if (level[u] < level[v]) {
        swap(u, v);
    }
    int diff = level[u] - level[v];
    for (int j = 0; j < LG; ++j) {
        if ((diff >> j) & 1) {
            u = up[u][j];
        }
    }
    if (u == v) {
        return u;
    }
    for (int j = LG - 1; j >= 0; --j) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j], v = up[v][j];
        }
    }
    return up[u][0];
}
