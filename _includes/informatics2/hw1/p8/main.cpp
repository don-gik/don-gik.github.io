#include <bits/stdc++.h>



using namespace std;

typedef long long ll;


class Solver {
    private:
        queue<ll> q;
        map<ll, ll> p;

        vector<ll> v;
    public:
        ll l;
        int n, k;

        void addValue(ll x) {
            q.push(x);
            p[x] = 1;

            return;
        }

        void solve(void) {
            int iteration = 0;

            while(iteration < k && !q.empty()) {
                auto cur = q.front();
                
                v.push_back(p[cur]);
                q.pop();

                if((!p[cur+1]) && cur < l) q.push(cur+1), p[cur+1] = p[cur] + 1;
                if((!p[cur-1]) && cur > 0) q.push(cur-1), p[cur-1] = p[cur] + 1;

                iteration++;
            }
        }

        vector<ll> getAns(void) {
            for(int i=0; i<v.size(); i++) v[i]--;

            return v;
        }
};


Solver solver;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> solver.l >> solver.n >> solver.k;
    for(int i=0; i<solver.n; i++) {
        ll a;
        cin >> a;

        solver.addValue(a);
    }

    solver.solve();

    for(auto it : solver.getAns()) {
        cout << it << "\n";
    }


    return 0;
}