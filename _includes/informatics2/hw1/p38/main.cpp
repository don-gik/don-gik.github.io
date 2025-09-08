#include <bits/stdc++.h>



using namespace std;


const int MAXN = 25e4; // How Solve?????


struct Segment {
    int tree[MAXN*4 + 10];

    void init(int n) {
        for(int i=0; i<4*n+1; i++) tree[i] = 0;
    }

    void update(int node, int tl, int tr, int pos, int val) {
        if(tl > pos || pos > tr) return;
        if(tl == tr) {
            tree[node] = max(tree[node], val);
            return;
        }

        int mid = tl + tr >> 1;

        update(node*2, tl, mid, pos, val);
        update(node*2+1, mid+1, tr, pos, val);

        tree[node] = max(tree[node*2], tree[node*2+1]);

        return;
    }

    int query(int node, int tl, int tr, int l, int r) {
        if(tl > r || l > tr) return 0;
        if(l <= tl && tr <= r) return tree[node];

        int mid = tl + tr >> 1;

        return max(query(node*2, tl, mid, l, r), query(node*2+1, mid+1, tr, l, r));
    }
};


int n;
int a[MAXN + 10];

int dp[MAXN + 10];

Segment seg;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for(int i=0; i<n; i++) cin >> a[i];

    int start = n;
    for(int i=0; i<n; i++) if(a[i] == 1) { start = i; break; }


    // cout << start << "\n";


    for(int i=start; i<n; i++) {
        int q = seg.query(1, 1, n, a[i]-1, a[i]-1);
        dp[i] = (q == 0 && a[i] != 1 ? -1 : q) + 1;
        seg.update(1, 1, n, a[i], dp[i]);

        // cout << dp[i] << " ";
    }

    // cout << endl;


    cout << n - seg.query(1, 1, n, 1, n);


    return 0;
}