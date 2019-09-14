bool bellman(int s) {
    fill(d, d + n + 1, LINF);
    d[s] = 0;
    bool last;
    for (int i = 0; i < n; ++i) {
        last = false;
        for (auto &x: e) {
            if (d[x.u] < LINF) {
                if (d[x.v] > d[x.u] + x.dis) {
                    d[x.v] = max(-LINF, d[x.u] + x.dis);
                    p[x.v] = x.u;
                    last = (x.v > 0);
                }
            }
        }
    }
    return !last;
}
