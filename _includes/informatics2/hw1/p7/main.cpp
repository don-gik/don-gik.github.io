#include <bits/stdc++.h>



using namespace std;


class Solver {
private:
    int l, r, s;
public:
    void setValue(int L, int R, int S) {
        l = L, r = R, s = S;
        return;
    }

    int solve(void) {
        return min((s - l) * 2 + 1, (r - s) * 2);
    }
};


int t;
Solver solver;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> t;
    for(int i=0; i<t; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        solver.setValue(a, b, c);
        cout << solver.solve() << "\n";
    }


    return 0;
}