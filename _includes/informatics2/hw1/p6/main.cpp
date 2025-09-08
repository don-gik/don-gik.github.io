#include <bits/stdc++.h>



using namespace std;


struct Point{
    int x;
    int y;

    Point(int X, int Y) : x(X), y(Y) {}
};

class Solver {
private:
    static const int MAXN = 1e5;
    static const int INF = 2e9;

    int minVal = INF;

public:
    int n;
    vector<Point> p;

    void solve(void) {
        int lowestY = 0;
        int highestY = 0;
        
        int sidel1 = 0;
        int sidel2 = 0;

        int sider1 = 0;
        int sider2 = 0;


        auto cmpByY = [&](const Point &x, const Point &y) {
            return x.y < y.y;
        };
        sort(p.begin(), p.end(), cmpByY);
        lowestY = p[0].y, highestY = p[p.size() - 1].y;

        auto cmpBySide1 = [&](const Point &x, const Point &y) {
            return (x.x + x.y) < (y.x + y.y);
        };
        sort(p.begin(), p.end(), cmpBySide1);
        sidel1 = p[0].x + p[0].y;
        sidel2 = p[p.size() - 1].x + p[p.size() - 1].y;

        auto cmpBySide2 = [&](const Point &x, const Point &y) {
            return (- x.x + x.y) < (- y.x + y.y);
        };
        sort(p.begin(), p.end(), cmpBySide2);
        sider1 = - p[0].x + p[0].y;
        sider2 = - p[p.size() - 1].x + p[p.size() - 1].y;

        // cout << sidel1 << " " << sidel2 << endl;
        // cout << sider1 << " " << sider2 << endl;
        // cout << lowestY << " " << highestY << endl;

        minVal = min(sider2 + sidel2 - 2*lowestY, - sider1 - sidel1 + 2*highestY);


        return;
    }

    int ans(void) {
        return minVal;
    }
};


Solver solver;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> solver.n;
    for(int i=0; i<solver.n; i++) {
        int a, b;
        cin >> a >> b;
        solver.p.push_back(Point(a, b));
    }

    solver.solve();
    cout << solver.ans();



    return 0;
}