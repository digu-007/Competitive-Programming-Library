int find_set(int v) {
    return (v == p[v] ? v : p[v] = find_set(p[v]));
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sz[a] < sz[b]) {
            swap(a, b);
        }
        p[b] = a;
        sz[a] += sz[b];
    }
}
