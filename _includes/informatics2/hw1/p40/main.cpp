#include <bits/stdc++.h>



using namespace std;



const int MAXN = 25e4;


struct UnionFind {
    int par[MAXN + 10] = {};
    int depth[MAXN + 10] = {};
    int cnt[MAXN + 10] = {};

    void init(int n) {
        for(int i=1; i<=n; i++) {
            par[i] = i;
            depth[i] = 1;
            cnt[i] = 1;
        }
    }

    int find(int node) {
        if(par[node] == node) return node;
        par[node] = find(par[node]);
        return par[node];
    }

    void merge(int x, int y) {
        x = find(x);
        y = find(y);

        if(depth[x] > depth[y]) swap(x, y);

        if(depth[x] == depth[y]) depth[y]++;

        par[x] = y;

        cnt[y] += cnt[x];

        return;
    }
};


int n;
int q, k;

vector<int> edge[MAXN + 10];
int s[MAXN + 10];
bool ins[MAXN + 10];

int par[MAXN + 10];

UnionFind uf;


void getPar(int current, int last) {
    par[current] = last;

    for(auto it : edge[current]) {
        if(it == last) continue;

        getPar(it, current);
    }

    return;
}

int solve(void) {
    int ans = 0;

    for(int i=0; i<k; i++) {
        uf.depth[s[i]] = 1;
        uf.par[s[i]] = s[i];
        uf.cnt[s[i]] = 1;
    }

    for(int i=0; i<k; i++) {
        if(ins[par[s[i]]]) {
            uf.merge(par[s[i]], s[i]);
            //cout << "merged \n";
        }

        // cout << par[s[i]] << " " << s[i] << " " << ins[par[s[i]]] << "\n";
    }
    // cout << "\n";

    for(int i=0; i<k; i++) {
        if(uf.find(s[i]) == s[i]) {
            ans += uf.cnt[s[i]] * (uf.cnt[s[i]] - 1) / 2;
        }

        // cout << uf.cnt[s[i]] << " ";
    }
    // cout << endl;

    // for(int i=0; i<k; i++) {
    //     cout << uf.par[s[i]] << " " << s[i] << "\n";
    // }
    // cout << endl;

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for(int i=0; i<n-1; i++) {
        int a, b;
        cin >> a >> b;

        edge[a].push_back(b);
        edge[b].push_back(a);
    }

    getPar(1, 0);

    
    cin >> q;
    for(int i=0; i<q; i++) {
        cin >> k;
        
        for(int j=0; j<k; j++) {
            cin >> s[j];
            ins[s[j]] = true;
        }

        cout << solve() << "\n";
        
        for(int j=0; j<k; j++) ins[s[j]] = false;
    }
    


    return 0;
}