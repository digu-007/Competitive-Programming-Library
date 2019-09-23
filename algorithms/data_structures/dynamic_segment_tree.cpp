struct seg{
	ll val;
	seg *l, *r;
	seg() {
		l = r = NULL;
		val = 0;
	}
};

void update(seg &v, ll tl, ll tr, ll pos, ll val){
	if (tl == tr){
		v.val = val;
		return;
	}
	if (!v.r) {
        v.r = new seg;
    }
	if (!v.l) {
        v.l = new seg;
    }
	if (pos <= mid){
		update(*v.l, tl, mid, pos, val);
	} else {
        update(*v.r, mid + 1, tr, pos, val);
	}
    v.val = v.l -> val + v.r -> val;
}

ll query(seg &v, ll tl, ll tr, ll l, ll r){
	if (tl > r or tr < l){
		return 0;
	}
	if (tl >= l and tr <= r){
		return v.val;
	}
    ll ans = 0;
    if (!(tl > r or mid < l)){
        if (!v.l) {
            v.l = new seg;
        }
        ans = query(*v.l, tl, mid, l, r);
	}
    if (!(mid + 1 > r or tr < l)){
        if (!v.r) {
            v.r = new seg;
        }
        ans += query(*v.r, mid + 1, tr, l, r);
	}
	return ans;
}
