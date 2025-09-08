#include <bits/stdc++.h>


using namespace std;


struct Stats {
    int gold;
    int silver;
    int bronze;
    int index;
    bool isTheCountry;

    Stats(void) : gold(0), silver(0), bronze(0), index(0), isTheCountry(false) {}
    Stats(int G, int S, int B, int I, bool X) : gold(G), silver(S), bronze(B), index(I), isTheCountry(X) {}

    bool operator<(const Stats &other) const {
        if(gold == other.gold
        && silver == other.silver
        && bronze == other.bronze) return isTheCountry;
        if(gold == other.gold) {
            if(silver == other.silver) {
                return bronze > other.bronze;
            }
            return silver > other.silver;
        }
        return gold > other.gold;
    }
};

const int MAXN = 1e3;


int n, k;

Stats stats[MAXN + 10];


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> k;
    for(int i=0; i<n; i++) {
        int m, g, s, b;
        cin >> m >> g >> s >> b;

        stats[m-1] = Stats(g, s, b, m, m==k);
    }

    sort(stats, stats+n);

    for(int i=0; i<n; i++) {
        if(stats[i].index == k) {
            cout << i+1;
            return 0;
        }
    }

    cout << "Error";


    return 0;
}