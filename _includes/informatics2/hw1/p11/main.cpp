#include <bits/stdc++.h>



using namespace std;




struct Thing {
    int x;
    int t;

    Thing(int X, int T) : x(X), t(T) {}

    bool operator<(const Thing &a) const {
        return x < a.x;
    }
};

struct Input {
    int n;
    vector<Thing> v;
};


class Solver {

private:
    int n;
    vector<Thing> v;

    int ans;

public:
    void getInput(Input a);
    void solve(void);
    int getOutput(void);
};



void Solver::getInput(Input a) {
    n = a.n;
    v = a.v;

    return;
}

void Solver::solve(void) {
    v.push_back(Thing(0, 0));

    sort(v.begin(), v.end());

    int curX = (*(v.end() - 1)).x;
    int curT = (*(v.end() - 1)).x;

    for(int i=v.size()-1; i>=0; i--) {
        curT = max(v[i].t, abs(curX - v[i].x) + curT);
        curX = v[i].x;
    }

    ans = curT;

    return;
}

int Solver::getOutput(void) {
    return ans;
}


Solver solver;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    Input x;
    cin >> x.n;
    for(int i=0; i<x.n; i++) { int a; cin >> a; x.v.push_back({a, 0}); }
    for(int i=0; i<x.n; i++) { int a; cin >> a; x.v[i].t = a; }

    solver.getInput(x);
    solver.solve();
    
    cout << solver.getOutput();


    return 0;
}