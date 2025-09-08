#include <bits/stdc++.h>



using namespace std;


struct Point {
    int x;
    int y;

    Point(int X, int Y) : x(X), y(Y) {}
};

struct Input {
    int n;
    vector<Point> p;
};

struct Output {
    long long ans;

    Output(long long Ans) : ans(Ans) {}
};


class Solver {

private:
    static const int INF = 2e9;
    static const int MAXN = 1e5;

    int n;
    vector<Point> p;

    vector<long long> l;
    vector<int> v[MAXN + 10];

public:
    void getInput(Input x);
    void solve(void);
    Output getOutput(void);

    void debug(void);
};

void Solver::getInput(Input x) {
    n = x.n;
    p = x.p;

    return;
}

void Solver::solve(void) {
    auto cmp = [&](const Point &x, const Point &y) {
        return x.x < y.x;
    };
    sort(p.begin(), p.end(), cmp);

    for(auto it : p) {
        v[it.y].push_back(it.x);
    }

    for(int i=0; i<=n; i++) {
        if(v[i].size() < 1) continue;
        
        if(v[i].size() == 1) { l.push_back(0); continue; }

        l.push_back(v[i][1] - v[i][0]);
        if(v[i].size() > 2) {
            for(int j=1; j<v[i].size()-1; j++) {
                l.push_back(min(v[i][j] - v[i][j-1], v[i][j+1] - v[i][j]));
            }
        }
        l.push_back(v[i][v[i].size() - 1] - v[i][v[i].size() - 2]);

    }

    return;
}

Output Solver::getOutput(void) {
    return Output(accumulate(l.begin(), l.end(), 0LL));
}

void Solver::debug(void) {
    for(auto it : l) cout << it << " ";
    cout << "\n";

    return;
}


Solver solver;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    Input x;

    cin >> x.n;
    for(int i=0; i<x.n; i++) {
        int a, b; cin >> a >> b;
        x.p.push_back(Point(a, b));
    }

    solver.getInput(x);
    solver.solve();
    // solver.debug();
    cout << solver.getOutput().ans;



    return 0;
}