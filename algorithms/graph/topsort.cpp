bool topsort() {
    int indeg[n + 1] = {0};
    for (int i = 1; i <= n; ++i) {
        for (auto &x: g[i]) {
            ++indeg[x];
        }
    }
    MinPriorityQueue < int > pq;
    for (int i = 1; i <= n; ++i) {
        if (!indeg[i]) {
            pq.push(i);
        }
    }
    while (pq.size()) {
		int u = pq.top();
		pq.pop();
		order.eb(u);
		for (auto &v: g[u]) {
			--indeg[v];
			if (!indeg[v]) {
                pq.push(v);
            }
		}
	}
    return (order.size() == n ? true : false);
}
