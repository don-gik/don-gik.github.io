#include <bits/stdc++.h>



using namespace std;


const int MAXN = 50;
const int INF = 2e9;


struct Vec2 {
    int x;
    int y;

    Vec2() : x(0), y(0) {}
    Vec2(int X, int Y) : x(X), y(Y) {}
} typedef vec2;


int n, c;
vec2 pos[MAXN + 10];


int taxiDistance(vec2 a, vec2 b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int totalDistance(vector<int> v) {
    int res = 0;

    for(int i=0; i<n; i++) {
        int m = INF;
        for(auto it : v) {
            m = min(m, taxiDistance(pos[it], pos[i]));
        }

        res = max(res, m);
    }

    return res;
}

int main() {
	ios_base::sync_with_stdio();
    cin.tie(0);

    cin >> n >> c;
    for(int i=0; i<n; i++) {
        int x, y; 
        cin >> x >> y;
        pos[i] = vec2(x, y);
    }

    vector<int> v;
    v.resize(c);

    int ans = INF;

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            for(int k=0; k<n; k++) {
                if(c <= 1) {
                    v[0] = i;
                    ans = min(ans, totalDistance(v));
                }else if(c <= 2) {
                    v[0] = i;
                    v[1] = j;
                    ans = min(ans, totalDistance(v));
                }else if(c <= 3) {
                    v[0] = i;
                    v[1] = j;
                    v[2] = k;
                    ans = min(ans, totalDistance(v));
                }
            }
        }
    }

    cout << ans;



    return 0;
}
