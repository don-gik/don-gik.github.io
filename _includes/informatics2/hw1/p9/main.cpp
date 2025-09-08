#include <bits/stdc++.h>



using namespace std;


struct Bus {
    int s;
    int t;

    Bus(int S, int T) : s(S), t(T) {}
};

class Solver {

private:
    static const int MAXN = 100;

    int n, x;
    vector<Bus> v;

    int ans = -1;

public:
    void setValue(int N, int X, vector<Bus> V) {
        n = N, x = X;
        v = V;
        return;
    }

    void solve(void) {
        auto cmp = [&](const Bus &x, const Bus &y) {
            return x.s > y.s;
        };  
        sort(v.begin(), v.end(), cmp);

        for(auto bus : v) {
            if(bus.s + bus.t <= x) {
                ans = bus.s;
                break;
            }
        }

        return;
    }

    int getAns(void) {
        return ans;
    }
};


Solver solver;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, x;
    vector<Bus> v;

    cin >> n >> x;
    for(int i=0; i<n; i++) { int a, b; cin >> a >> b; v.push_back(Bus(a, b)); }


    solver.setValue(n, x, v);
    solver.solve();
    cout << solver.getAns();


    return 0;
}