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

#ifndef ONLINE_JUDGE
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

const ll LINF = LLONG_MAX, base = 1e9, MOD = 1e9 + 7, N = 1e4 + 5, M = 1e3 + 5;
const int INF = INT_MAX;
const db PI = acos(-1), EPS = 1 / db(1e6);

struct pnt{
    int x, y;
};

struct event{
    int idx;
    bool typ;
    event() {};
    event(int idx, bool typ) : idx(idx), typ(typ) {};
};

int n, e;
pnt rect[N][2];
event events_h[2 * N], events_v[2 * N];

void test();
ll union_area();

int main() {
    fast_io();
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    cout << fixed << setprecision(15);
    test();
    #ifndef ONLINE_JUDGE
        cout << "Time: " << (int)(clock() * 1000. / CLOCKS_PER_SEC) << "ms";
    #endif
    return 0;
}

void test() {
    cin >> n;
    e = 2 * n;
    for (int i = 0; i < n; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        rect[i][0].x = a, rect[i][0].y = b;
        rect[i][1].x = c, rect[i][1].y = d;
        events_h[2 * i].idx = i, events_h[2 * i].typ = false;
        events_h[2 * i + 1].idx = i, events_h[2 * i + 1].typ = true;
        events_v[2 * i].idx = i, events_v[2 * i].typ = false;
        events_v[2 * i + 1].idx = i, events_v[2 * i + 1].typ = true;
    }
    cout << union_area() << "\n";
}

ll union_area() {
    bool in_set[N] = {false};
    ll ans = 0;
    sort(events_v, events_v + e, [&](event a, event b) {
        return rect[a.idx][a.typ].x < rect[b.idx][b.typ].x;
    });
    sort(events_h, events_h + e, [&](event a, event b) {
        return rect[a.idx][a.typ].y < rect[b.idx][b.typ].y;
    });
    in_set[events_v[0].idx] = true;
    for (int i = 1; i < e; ++i) {
        event cur = events_v[i];
        int cnt = 0, begin_y = 0, del_x = rect[cur.idx][cur.typ].x - rect[events_v[i - 1].idx][events_v[i - 1].typ].x;
        if (!del_x) {
            in_set[cur.idx] = (cur.typ == false);
            continue;
        }
        for (int j = 0; j < e; ++j) {
            if (in_set[events_h[j].idx]) {
                if (!events_h[j].typ) {
                    if (!cnt) {
                        begin_y = rect[events_h[j].idx][0].y;
                    }
                    ++cnt;
                } else {
                    --cnt;
                    if (!cnt) {
                        int del_y = rect[events_h[j].idx][1].y - begin_y;
                        ans += 1ll * del_x * del_y;
                    }
                }
            }
        }
        in_set[cur.idx] = (cur.typ == false);
    }
    return ans;
}
