void dfs(int s, int p) {
    tin[s] = ++timer;
    up[s][0] = p;
    for (int i = 1; i <= lg; ++i) {
        up[s][i] = up[up[s][i - 1]][i - 1];
    }
    for (auto &x: g[s]) {
        if (x.F != p) {
            pre[x.F] = pre[s] + ll(x.S);
            dfs(x.F, s);
        }
    }
    tout[s] = ++timer;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] and tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) {
        return u;
    }
    if (is_ancestor(v, u)) {
        return v;
    }
    for (int i = lg; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}

ll dist(int u, int v) {
    return pre[u] + pre[v] - 2 * pre[lca(u, v)];
}

void binary_lifting(int root) {
    lg = ceil(log2(n + 1));
    up.resize(n + 1);
    for (int i = 0; i <= n; ++i) {
        up[i].resize(lg + 1);
    }
    dfs(root, root);
}
