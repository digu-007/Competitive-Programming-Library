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

const ll LINF = LLONG_MAX, base = 1e9, MOD = 1e9 + 7, N = 1e4 + 5, M = 2e4 + 5, LG = 20;
const int INF = INT_MAX;
const db PI = acos(-1), EPS = 1 / db(1e6);
mt19937_64 rang(chrono::high_resolution_clock::now().time_since_epoch().count());

int n, h, v, bit[N];
vector < pair < int, pii > > ver;
vector < pair < pii, int > > hor;

void update(int x, int y) {
    for (; x < N; x = x | (x + 1)) {
        bit[x] += y;
    }
}

ll sum(int x) {
    ll ans = 0;
    for (; x >= 0; x = (x & (x + 1)) - 1) {
        ans += bit[x];
    }
    return ans;
}

void test() {
    cin >> n;
    for (int i = 0, a, b, c, d; i < n; ++i) {
        cin >> a >> b >> c >> d;
        a += 5000, b += 5000, c += 5000, d += 5000;
        if (a == c) {
            ver.pb({a, {min(b, d), max(b, d)}});
        } else {
            hor.pb({{min(a, c), max(a, c)}, b});
        }
    }
    sort(all(ver));
    sort(all(hor));
    h = hor.size(), v = ver.size();
    ll ans = 0;
    for (int i = 0; i < v; ++i) {
        vector < pii > ok;
        for (int i = 0; i < N; ++i) {
            bit[i] = 0;
        }
        for (auto &p: hor) {
            if (p.S <= ver[i].S.S and p.S >= ver[i].S.F and p.F.F <= ver[i].F and p.F.S > ver[i].F) {
                ok.pb({p.F.S, p.S});
                update(p.S, 1);
            }
        }
        sort(all(ok));
        int k = 0;
        for (int j = i + 1; j < v; ++j) {
            while (k < ok.size() and ver[j].F > ok[k].F) {
                update(ok[k++].S, -1);
            }
            int lo = ver[j].S.F, hi = ver[j].S.S;
            int cur = sum(hi) - sum(lo - 1);
            ans += (1ll * cur * (cur - 1)) / 2;
        }
    }
    cout << ans << "\n";
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
