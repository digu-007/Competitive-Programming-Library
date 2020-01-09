struct Edge {
    int u, v, idx;
    ll cap, flow;
    Edge() {}
    Edge(int u, int v, ll cap, ll flow, int idx): u(u), v(v), cap(cap), flow(flow), idx(idx) {}
    Edge(int u, int v, ll cap, int idx): u(u), v(v), cap(cap), flow(0ll), idx(idx) {}
};

struct PushRelabel {
    const ll flow_inf = 1e18;
    int n;
    vector<vector<Edge>> g;
    vll excess;
    vi height;

    PushRelabel(int n): n(n), g(n), excess(n), height(n) {}

    void AddEdge(int u, int v, ll cap) {
        g[u].eb(Edge(u, v, cap, g[v].size()));
        if (u == v) {
            ++g[u].back().idx;
        }
        g[v].eb(Edge(v, u, 0, g[u].size() - 1));
    }

    void push(Edge &e) {
        ll amt = min(excess[e.u], e.cap - e.flow);
        if (height[e.u] <= height[e.v] or !amt) return;
        e.flow += amt;
        g[e.v][e.idx].flow -= amt;
        excess[e.v] += amt;
        excess[e.u] -= amt;
    }

    void relabel(int u) {
        int d = INF;
        for (auto &x: g[u]) {
            if (x.cap - x.flow > 0) {
                d = min(d, height[x.v]);
            }
        }
        height[u] = d + 1;
    }

    vector<int> MaxHeightVertices(int s, int t) {
        vi ans;
        for (int i = 0; i < n; ++i) {
            if (i != s and i != t and excess[i] > 0) {
                if (ans.size() and height[i] > height[ans.front()]) {
                    ans.clear();
                }
                if (ans.empty() or height[i] == height[ans.front()]) {
                    ans.eb(i);
                }
            }
        }
        return ans;
    }

    long long MaxFlow(int s, int t) {
        excess.assign(n, 0);
        height.assign(n, 0);
        height[s] = n;
        excess[s] = flow_inf;
        for (auto &x: g[s]) {
            push(x);
        }
        vi cur;
        while (!(cur = MaxHeightVertices(s, t)).empty()) {
            for (auto i: cur) {
                bool pushed = false;
                for (auto &e: g[i]) {
                    if (!excess[i]) break;
                    if (e.cap - e.flow > 0 and height[e.u] == height[e.v] + 1) {
                        push(e);
                        pushed = true;
                    }
                }
                if (!pushed) {
                    relabel(i);
                    break;
                }
            }
        }
        ll ans = 0;
        for (auto &e: g[s]) {
            ans += e.flow;
        }
        return ans;
    }
};
