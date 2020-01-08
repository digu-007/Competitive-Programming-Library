struct Edge {
    int u, v;
    ll cap, flow;
    Edge() {}
    Edge(int u, int v, ll cap): u(u), v(v), cap(cap), flow(0) {}
};

struct Dinic {
    int n;
    vector<Edge> e;
    vector<vi> g;
    vi d, pt;

    Dinic(int n): n(n), e(0), g(n), d(n), pt(n) {}

    void AddEdge(int u, int v, ll cap) {
        if (u != v) {
            e.eb(Edge(u, v, cap));
            g[u].eb(e.size() - 1);
            e.eb(Edge(v, u, 0));
            g[v].eb(e.size() - 1);
        }
    }

    bool bfs(int s, int t) {
        queue<int> q;
        q.push(s);
        fill(d.begin(), d.end(), n + 1);
        d[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == t) break;
            for (int k: g[u]) {
                Edge &ee = e[k];
                if (ee.flow < ee.cap and d[ee.v] > d[ee.u] + 1) {
                    d[ee.v] = d[ee.u] + 1;
                    q.push(ee.v);
                }
            }
        }
        return (d[t] != n + 1);
    }

    ll dfs(int u, int t, ll flow = -1) {
        if (u == t or !flow) {
            return flow;
        }
        for (int &i = pt[u]; i < g[u].size(); ++i) {
            Edge &ee = e[g[u][i]];
            Edge &oe = e[g[u][i] ^ 1];
            if (d[ee.v] == d[ee.u] + 1) {
                ll amt = ee.cap - ee.flow;
                if (flow != -1 and amt > flow) {
                    amt = flow;
                }
                if (ll pushed = dfs(ee.v, t, amt)) {
                  ee.flow += pushed;
                  oe.flow -= pushed;
                  return pushed;
                }
            }
        }
        return 0;
    }

    ll MaxFlow(int s, int t) {
        ll ans = 0;
        while (bfs(s, t)) {
            fill(pt.begin(), pt.end(), 0);
            while (ll flow = dfs(s, t)) {
                ans += flow;
            }
        }
        return ans;
    }
};
