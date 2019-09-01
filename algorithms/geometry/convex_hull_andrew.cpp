struct pnt{
    double x, y;
};

bool cross(pnt a, pnt b, pnt c) {
    return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) <= 0);
}

vector < pnt > convex_hull(vector < pnt > p) {
    int j = 0, n = p.size();
    vector < pnt > hull(2 * n);
    sort(all(p), [&](pnt a, pnt b) {
        return a.x < b.x or (a.x == b.x and a.y < b.y);
    });
    for (int i = 0; i < n; ++i) {
        while (j > 1 and cross(hull[j - 2], hull[j - 1], p[i])) {
            --j;
        }
        hull[j++] = p[i];
    }
    for (int i = n - 2, cur = j + 1; i >= 0; --i) {
        while (j >= cur and cross(hull[j - 2], hull[j - 1], p[i])) {
            --j;
        }
        hull[j++] = p[i];
    }
    hull.resize(j - 1);
    return hull;
}
