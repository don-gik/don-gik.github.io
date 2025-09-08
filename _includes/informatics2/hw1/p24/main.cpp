#include <bits/stdc++.h>



using namespace std;

typedef pair<int, int> pii;


const int MAXN = 1e3;
const pii MOVE[4] = {
    {1, 0},
    {-1, 0},
    {0, -1},
    {0, 1}
};


int n, m;
int a[MAXN + 10][MAXN + 10];

queue<pii> q;
int vis[MAXN + 10][MAXN + 10];



bool isInside(int x, int y) {
    return ((x >= 0 && x < n) && (y >= 0 && y < m));
}

int bfs(void) {
    int res = 0;

    while(!q.empty()) {
        auto cur = q.front();
        // cout << cur.first << " " << cur.second << "\n";
        q.pop();


        for(auto it : MOVE) {
            auto next = make_pair(cur.first + it.first, cur.second + it.second);
            if(isInside(next.first, next.second) 
                && vis[next.first][next.second] == 0
                && a[next.first][next.second] == 0) {
                
                vis[next.first][next.second] = vis[cur.first][cur.second] + 1;
                res = max(res, vis[next.first][next.second]);
                q.push(next);
            }
        }
    }

    return res;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> m >> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            int x;
            cin >> x;
            a[i][j] = x;
            if(x == 1) q.push({i, j}), vis[i][j] = 1;
        }
    }


    int turn = bfs() - 1;


    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            // cout << vis[i][j] << " ";
            if(a[i][j] == 0 && vis[i][j] == 0) {
                cout << -1;
                return 0;
            }
        }
        // cout << "\n";
    }

    cout << turn;


    return 0;
}