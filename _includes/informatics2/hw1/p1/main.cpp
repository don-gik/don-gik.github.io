#include <bits/stdc++.h>


using namespace std;


struct State {
    int x;

    State(int X) : x(X) {}

    vector<State> availableState(void) {
        vector<State> v;
        v.push_back(State(x+1));
        v.push_back(State(x+2));

        return v;
    }
};


const int MAXN = 25e4;

int n;
bool obstacle[MAXN + 10];

int vis[MAXN + 10];
queue<State> q;

int lastObstacle = 0;

int bfs(int start) {
    q.push(State(start));
    vis[start] = 1;

    while(!q.empty()) {
        auto p = q.front();
        q.pop();

        for(auto it : p.availableState()) {
            if((!obstacle[it.x]) && (!vis[it.x]) && it.x < lastObstacle+2) {
                vis[it.x] = vis[p.x] + 1;
                q.push(it);
            }
        }
    }


    return vis[lastObstacle+1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for(int i=0; i<n; i++) {
        int a;
        cin >> a;
        obstacle[a] = true;
        
        lastObstacle = max(lastObstacle, a);
    }

    cout << bfs(0) - 1;


    return 0;
}