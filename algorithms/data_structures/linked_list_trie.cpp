struct trie {
    trie* next[2];
    int cnt = 0;
};

trie* head;

void add(int x) {
    trie* cur = head;
    for (int i = N; i >= 0; --i) {
        bool bit = (x >> i) & 1;
        if (cur -> next[bit] == NULL) {
            cur -> next[bit] = new trie();
        }
        cur = cur -> next[bit];
        ++cur -> cnt;
    }
}

void remove(int x) {
    trie* cur = head;
    for (int i = N; i >= 0; --i) {
        bool bit = (x >> i) & 1;
        cur = cur -> next[bit];
        --cur -> cnt;
    }
}

int query(int x) {
    trie* cur = head;
    int ans = 0;
    for (int i = N; i >= 0; --i) {
        bool bit = !((x >> i) & 1);
        if (cur -> next[bit] and cur -> next[bit] -> cnt) {
            ans += (1 << i);
            cur = cur -> next[bit];
        } else {
            cur = cur -> next[!bit];
        }
    }
    return ans;
}
