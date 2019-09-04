void dfs(int s) {
    vis[s] = true;
    for (auto &x: g[s]) {
        if (!vis[x]) {
            dfs(x);
        }
    }
    order.eb(s);
}

void dfs2 (int s) {
    vis[s] = true;
    comp[cnt].eb(s);
    for (auto &x: g2[s]) {
        if (!vis[x]) {
            dfs2(x);
        }
    }
}

void scc() {
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            dfs(i);
        }
    }
    fill(vis, vis + n + 1, false);
    reverse(all(order));
    for (auto &x: order) {
        if (!vis[x]) {
            dfs2(x);
            ++cnt;
        }
    }
}
