void dijkstra(int s) {
    fill(d, d + n + 1, ll(1e18));
    fill(p, p + n + 1, -1);
    d[s] = 0;
    priority_queue < pair < ll, int >, vector < pair < ll, int > >, greater < pair < ll, int > > > pq;
    pq.push({0, s});
    while (!pq.empty()) {
        int v = pq.top().S;
        int d_v = pq.top().F;
        pq.pop();
        if (d_v != d[v]) {
            continue;
        }
        for (auto &x: g[v]) {
            if (d[v] + x.S < d[x.F]) {
                d[x.F] = d[v] + x.S;
                p[x.F] = v;
                pq.push({d[x.F], x.F});
            }
        }
    }
}
