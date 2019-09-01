mt19937_64 rang(chrono::high_resolution_clock::now().time_since_epoch().count());

ll my_rand(ll l, ll r) {
    if (l > r) {
        swap(l, r);
    }
    uniform_int_distribution < int > uid(l, r);
    return uid(rang);
}
