#include <bits/stdc++.h>



using namespace std;



class Solver {
private:
    int k;
    int c;
    vector<int> n, m;

    vector<int> ans;

    void getPossible(int a, int b);

public:
    void getInput(void);
    void solve(void);
    void output(void);
};

void Solver::getPossible(int a, int b) {
    if(a > b) {
        if(b + k >= 2*a - 2) ans.push_back(1);
        else ans.push_back(0);
    }else {
        if(a + k >= 2*b - 1) ans.push_back(1);
        else ans.push_back(0);
    }
}

void Solver::getInput(void) {
    cin >> k;
    cin >> c;

    for(int i=0; i<c; i++) {
        int a, b;
        cin >> a >> b;

        n.push_back(a);
        m.push_back(b);
    }

    return;
}

void Solver::solve(void) {
    for(int i=0; i<c; i++) {
        if(n[i] > m[i]) {
            getPossible(n[i], m[i]);
        }else if(n[i] == m[i]) {
            if(n[i] <= k) ans.push_back(1);
            else ans.push_back(0);
        }else {
            getPossible(n[i], m[i]);
        }
    }

    return;
}

void Solver::output(void) {
    for(auto it : ans) cout << it << "\n";
}


Solver solver;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    solver.getInput();
    solver.solve();
    solver.output();


    return 0;
}