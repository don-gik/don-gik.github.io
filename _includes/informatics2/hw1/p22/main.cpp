#include <bits/stdc++.h>



using namespace std;


struct Point {
    int x;
    int y;

    Point(void) : x(0), y(0) {}
    Point(int X, int Y) : x(X), y(Y) {}
};

const int MAXN = 1e5;

int m, n, l;

int a[MAXN + 10];
Point b[MAXN + 10];

int ans;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> m >> n >> l;
    for(int i=0; i<m; i++) cin >> a[i];
    
    sort(a, a+m);

    for(int i=0; i<n; i++) {
        int x, y;
        cin >> x >> y;

        b[i] = Point(x, y);
    }

    sort(b, b+n, [&](const Point &x, const Point &y) {
        return x.x < y.x;
    });


    int ind = 0;

    for(int i=0; i<n; i++) {
        while(ind < m-1 &&
            abs(b[i].x - a[ind]) > abs(b[i].x - a[ind+1])) {
            
            ind++;
        }

        // cout << ind << " ";

        if(abs(b[i].x - a[ind]) + b[i].y <= l) ans++;
    }
    // cout << "\n";


    cout << ans;


    return 0;
}