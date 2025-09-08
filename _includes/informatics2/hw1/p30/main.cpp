#include <bits/stdc++.h>



using namespace std;


struct vec2 {
    int x;
    int y;

    vec2(void) : x(0), y(0) {}
    vec2(int X, int Y) : x(X), y(Y) {}

    vec2 operator+(const vec2 &other) {
        return vec2(other.x + x, other.y + y);
    }

    bool operator==(const vec2 &other) {
        return (other.x == x && other.y == y);
    }
};

const int MAXN = 50;
const vec2 MOVE[4] = {
    vec2(1, 0),
    vec2(0, 1),
    vec2(-1, 0),
    vec2(0, -1)
};

const vec2 MAP[12][2] = {
    {vec2(-1, 0), vec2(0, 1)},
    {vec2(0, -1), vec2(1, 0)},
    
    {vec2(1, 0), vec2(0, 1)},
    {vec2(0, -1), vec2(-1, 0)},

    {vec2(-1, 0), vec2(0, -1)},
    {vec2(0, 1), vec2(1, 0)},

    {vec2(1, 0), vec2(0, -1)},
    {vec2(0, 1), vec2(-1, 0)},

    {vec2(0, 1), vec2(0, 1)},
    {vec2(0, -1), vec2(0, -1)},

    {vec2(-1, 0), vec2(-1, 0)},
    {vec2(1, 0), vec2(1, 0)}
};


struct State {
    vec2 pos;
    vec2 dir;
    bool car = false;
};

int n, k;

int m[MAXN + 10][MAXN + 10];

int vis[MAXN + 10][MAXN + 10];
queue<State> q;


vector<vec2> v;


bool isInside(vec2 pos) {
    return (pos.x >= 0 && pos.x <= n + 1
         && pos.y >= 0 && pos.y <= n + 1);
}

int bfsWith1(vec2 start) {
    vec2 end = vec2(n+1, n);

    vis[start.x][start.y] = 1;
    q.push({start, vec2(1, 0)});


    while(!q.empty()) {
        auto cur = q.front();
        q.pop();

        // cout << cur.pos.x << ", " << cur.pos.y << "  " << cur.dir.x << ", " << cur.dir.y << "\n";
        for(int i=0; i<2; i++) {
            auto next = cur.pos + cur.dir;
            auto nextPossible = MAP[m[next.x][next.y]*2 + i];
            // cout << nextPossible[0].x << ", " << nextPossible[0].y << "  " << nextPossible[1].x << ", " << nextPossible[1].y << "\n";

            if(cur.dir == nextPossible[0] && isInside(next) && vis[next.x][next.y] == 0) {
                q.push({next, nextPossible[1]});
                vis[next.x][next.y] = vis[cur.pos.x][cur.pos.y] + 1;
            }
        }
    }

    return vis[end.x][end.y] - 2;
}

int bfsWith2(void) {
    int res = 2e9;

    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            for(int k=0; k<6; k++) {
                if(m[j][i] == k) continue;

                for(int y=0; y<=n+1; y++) {
                    for(int x=0; x<=n+1; x++) {
                        vis[x][y] = 0;
                    }
                }
                while(!q.empty()) q.pop();

                int temp = m[j][i];

                m[j][i] = k;

                int c = bfsWith1(vec2(0, 1));

                if(c >= 0) res = min(c, res);

                m[j][i] = temp;
            }    
        }
    }

    return (res == 2e9 ? -1 : res); 
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> k;


    for(int i=0; i<=n+1; i++) {
        for(int j=0; j<=n+1; j++) {
            m[j][i] = -1;
        }
    }

    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            cin >> m[j][i];
        }
    }
    m[n+1][n] = 5;

    if(k == 0) { int c = bfsWith1(vec2(0, 1)); cout << (c < 0 ? -1 : c); }
    else cout << bfsWith2();


    return 0;
}