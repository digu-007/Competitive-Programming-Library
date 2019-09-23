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
typedef complex < double > com;
typedef gp_hash_table < int, int > fast;

#define eb emplace_back
#define pb push_back
#define F first
#define S second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define unique_sort(x) (sort(x.begin(), x.end()), x.resize(distance(x.begin(), unique(x.begin(), x.end()))))
#define fast_io() ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0)

const ll LINF = LLONG_MAX, base = 1e9, MOD = 1e9 + 7, N = 3e5 + 15, M = 1e3 + 5, LG = 20;
const int INF = INT_MAX;
const db PI = acos(-1), EPS = 1 / db(1e6);
mt19937_64 rang(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace ModFunctions {
	inline int add(int a, int b) {
		a += b;
		if (a >= MOD) {
			a -= MOD;
		}
        return a;
	}

	inline int sub(int a, int b) {
		a -= b;
		if (a < 0) {
			a += MOD;
		}
        return a;
	}

	inline int mul(int a, int b) {
		return int((1ll * a * b) % MOD);
	}

	inline int power(int a, ll b) {
		int res = 1;
		while (b > 0) {
			if (b & 1) {
				res = mul(res, a);
			}
			a = mul(a, a);
			b >>= 1;
		}
		return res;
	}

	inline int inv(int a) {
		a %= MOD;
		if (a < 0) {
			a += MOD;
		}
		int b = MOD, u = 0, v = 1;
		while (a) {
			int t = b / a;
			b -= t * a;
			swap(a, b);
			u -= t * v;
			swap(u, v);
		}
		assert(b == 1);
		if (u < 0) {
			u += MOD;
		}
		return u;
	}
}

using namespace ModFunctions;

int n, q, timer, from[N], to[N], tree1[4 * N], tree2[4 * N], level[N];
vi g[N];

void dfs(int s, int p, int lvl) {
    level[s] = lvl;
    from[s] = to[s] = ++timer;
    for (auto &x: g[s]) {
        if (x != p) {
            dfs(x, s, lvl + 1);
            to[s] = max(to[s], to[x]);
        }
    }
}

void update(int id, int tl, int tr, int v, int x, int k) {
    if (from[v] > tr or to[v] < tl) {
        return;
    }
    if (from[v] <= tl and to[v] >= tr) {
        tree1[id] = add(tree1[id], add(x, mul(level[v], k)));
        tree2[id] = add(tree2[id], k);
        return;
    }
    int mid = ((tl + tr) >> 1);
    update(2 * id, tl, mid, v, x, k);
    update(2 * id + 1, mid + 1, tr, v, x, k);
}

int query(int id, int tl, int tr, int v) {
    int ans = sub(tree1[id], mul(level[v], tree2[id]));
    if (tr <= tl) {
        return ans;
    }
    int mid = ((tl + tr) >> 1);
    if (from[v] <= mid) {
        return add(ans, query(2 * id, tl, mid, v));
    }
    return add(ans, query(2 * id + 1, mid + 1, tr, v));
}

void test() {
    cin >> n;
    for (int i = 2, j; i <= n; ++i) {
        cin >> j;
        g[i].eb(j);
        g[j].eb(i);
    }
    dfs(1, -1, 1);
    cin >> q;
    while (q--) {
        int a, v, x, k;
        cin >> a >> v;
        if (a == 1) {
            cin >> x >> k;
            update(1, 1, n, v, x, k);
        } else {
            cout << query(1, 1, n, v) << "\n";
        }
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
