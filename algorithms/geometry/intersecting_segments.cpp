/*
digu_J - Digvijay Janartha
NIT Hamirpur - INDIA
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("O3")

using namespace std;
using namespace __gnu_pbds;

template < typename T > using ordered_set = tree < T, null_type, less < T >, rb_tree_tag, tree_order_statistics_node_update >;
template < typename T > using MinPriorityQueue = priority_queue < T, vector < T >, greater < T > >;

#ifdef HOME
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template < typename Arg1 >
void __f(const char* name, Arg1&& arg1) {
    cout << name << " : " << arg1 << std :: endl;
}
template < typename Arg1, typename... Args >
void __f(const char* names, Arg1&& arg1, Args&&... args) {
    const char* comma = strchr(names + 1, ',');
    int len = comma - names;
    for (int i = 0; i < len; ++i) {
        cout << names[i];
    }
    cout <<  " : " << arg1 << " | ";
    __f(comma + 1, args...);
}
#else
#define trace(...)
#endif

typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair < ll, ll > pll;
typedef pair < int, int > pii;
typedef vector < ll > vll;
typedef vector < int > vi;
typedef gp_hash_table < int, int > fast;

#define eb emplace_back
#define pb push_back
#define F first
#define S second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define unique_sort(x) (sort(x.begin(), x.end()), x.resize(distance(x.begin(), unique(x.begin(), x.end()))))
#define fast_io() ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0)

const ll LINF = LLONG_MAX, base = 1e9, MOD = 1e9 + 7, N = 1e5 + 5, M = 1e3 + 5, LG = 20;
const int INF = INT_MAX;
const db PI = acos(-1), EPS = 1 / db(1e6);
mt19937_64 rang(chrono::high_resolution_clock::now().time_since_epoch().count());

struct pt{
    db x, y;
};

struct seg{
    pt p, q;
    int id;

    db get_y(db x) const {
        return (abs(p.x - q.x) < EPS ? p.y : p.y + (q.y - p.y) * (x - p.x) / (q.x - p.x));
    }
};

bool intersect1d(db l1, db r1, db l2, db r2) {
    if (l1 > r1) {
        swap(l1, r1);
    }
    if (l2 > r2) {
        swap(l2, r2);
    }
    return max(l1, l2) <= min(r1, r2) + EPS;
}

int vec(const pt& a, const pt& b, const pt& c) {
    db s = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return abs(s) < EPS ? 0 : s > 0 ? 1 : -1;
}

bool intersect(const seg& a, const seg& b) {
    return intersect1d(a.p.x, a.q.x, b.p.x, b.q.x) and intersect1d(a.p.y, a.q.y, b.p.y, b.q.y) and vec(a.p, a.q, b.p) * vec(a.p, a.q, b.q) <= 0 and vec(b.p, b.q, a.p) * vec(b.p, b.q, a.q) <= 0;
}

bool operator<(const seg& a, const seg& b) {
    double x = max(min(a.p.x, a.q.x), min(b.p.x, b.q.x));
    return a.get_y(x) < b.get_y(x) - EPS;
}

struct event {
    db x;
    int tp, id;

    event() {}
    event(double x, int tp, int id) : x(x), tp(tp), id(id) {}

    bool operator<(const event& e) const {
        if (abs(x - e.x) > EPS) {
            return x < e.x;
        }
        return tp > e.tp;
    }
};

set < seg > s;
vector < set < seg > :: iterator > where;

set < seg > :: iterator prev(set < seg > :: iterator it) {
    return it == s.begin() ? s.end() : --it;
}

set < seg > :: iterator next(set < seg > :: iterator it) {
    return ++it;
}

int n;
vector < seg > a;

pii solve() {
    vector < event > e;
    for (int i = 0; i < n; ++i) {
        e.pb(event(min(a[i].p.x, a[i].q.x), 1, i));
        e.pb(event(max(a[i].p.x, a[i].q.x), -1, i));
    }
    sort(all(e));
    s.clear();
    where.resize(a.size());
    for (size_t i = 0; i < e.size(); ++i) {
        int id = e[i].id;
        if (e[i].tp == 1) {
            auto nxt = s.lower_bound(a[id]), prv = prev(nxt);
            if (nxt != s.end() and intersect(*nxt, a[id]))
                return {nxt -> id, id};
            if (prv != s.end() and intersect(*prv, a[id])) {
                return {prv -> id, id};
            }
            where[id] = s.insert(nxt, a[id]);
        } else {
            auto nxt = next(where[id]), prv = prev(where[id]);
            if (nxt != s.end() and prv != s.end() and intersect(*nxt, *prv)) {
                return {prv -> id, nxt -> id};
            }
            s.erase(where[id]);
        }
    }
    return {-1, -1};
}

void test() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        db aa, b, c, d;
        cin >> aa >> b >> c >> d;
        pt x = {aa, b};
        pt y = {c, d};
        a.pb({x, y, i});
    }
    pii ans = solve();
    if (ans.F > ans.S) {
        swap(ans.F, ans.S);
    }
    cout << (ans.F == -1 ? "NO\n" : "YES\n");
    if (ans.F != -1) {
        cout << ans.F + 1 << " " << ans.S + 1 << "\n";
    }
}

int main() {
    fast_io();
    #ifdef HOME
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    cout << fixed << setprecision(15);
    test();
    #ifdef HOME
        cout << "Time: " << (int)(clock() * 1000. / CLOCKS_PER_SEC) << "ms";
    #endif
    return 0;
}
