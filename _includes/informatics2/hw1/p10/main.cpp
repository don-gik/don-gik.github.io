#include <bits/stdc++.h>



using namespace std;

typedef long long ll;


struct Input {
    int n;
    vector<ll> a;
};

class Solver {

private:
    int n;
    vector<ll> a;
    vector<ll> b;

    ll getValue(ll x, ll y, ll z) {
        ll exp = 0;

        // while(x < 1e18 && z < 1e18) x <<= 1, z <<= 1;

        // cout << x << " " << z << "\n";

        if(x > z) {
            exp = y+1;
            while(true) {
                if(x <= (z << (exp - y))) {
                    break;
                }

                exp++;
            }
        }else {
            exp = y-1;
            while(true) {
                if((x << (y - exp)) > z) {
                    break;
                }

                exp--;
            }
            exp++;

            exp = max(0LL, exp);
        }

        return exp;
    }

public:
    void getInput(Input x) {
        n = x.n;
        a = x.a;

        return;
    }

    void solve(void) {
        b.resize(n);

        for(int i=1; i<n; i++) {
            b[i] = (*this).getValue(a[i-1], b[i-1], a[i]);

            // cout << b[i] << " ";
        }
        // cout << "\n";
    }

    ll getOutput(void) {
        return accumulate(b.begin(), b.end(), 0LL);
    }
};


Solver solver;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    Input x;
    cin >> x.n;
    for(int i=0; i<x.n; i++) {
        ll a; cin >> a;
        x.a.push_back(a);
    }

    solver.getInput(x);
    solver.solve();
    cout << solver.getOutput();



    return 0;
}