void bfs(int s) {
    queue < int > q;
    q.push(s);
    vis[s] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto &x: g[v]) {
            if (!vis[x]) {
                vis[x] = true;
                q.push(x);
            }
        }
    }
}
