void bfs_01(int s) {
    fill(d, d + n + 1, int(1e9));
    d[s] = 0;
    deque < int > dq;
    dq.push_front(s);
    while (dq.size()) {
        int v = dq.front();
        dq.pop_front();
        for (auto &x: g[v]) {
            if (d[v] + x.S < d[x.F]) {
                d[x.F] = x.S + d[v];
                if (x.S) {
                    dq.pb(x.F);
                } else {
                    dq.push_front(x.F);
                }
            }
        }
    }
}
