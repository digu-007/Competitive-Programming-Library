db closest_pair() {
    sort(pnt, pnt + n, [&](pll a, pll b) {
        return a.S < b.S; // pnt is pair of coordinates(y, x)
    });
    db ans = DBL_MAX;
    set < pll > active;
    active.emplace(pnt[0]);
    int left = 0;
    for (int i = 1; i < n; ++i) {
        while (left < i and pnt[i].S - pnt[left].S > ans) {
            active.erase(pnt[left++]);
        }
        auto it = active.lower_bound({pnt[i].F - ans, pnt[i].S - ans});
        for(auto j = it; j != active.end() and pnt[i].F + ans >= j -> F; ++j) { 
            db cur = sqrt(pow(pnt[i].F - j -> F, 2.0) + pow(pnt[i].S - j -> S, 2.0));
            if (cur < ans) {
                fir = pnt[i], sec = {j -> F, j -> S}; // closest_pair
                ans = cur;
            }
        }
       active.emplace(pnt[i]);
    }
    return ans;
}
