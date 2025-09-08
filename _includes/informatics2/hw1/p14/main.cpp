#include <bits/stdc++.h>



using namespace std;


struct State {
    int x;
    int y;
    int t;


    State(void) : x(0), y(0), t(0) {}
    State(int X, int Y, int T) : x(X), y(Y), t(T) {}


    State fillA(int limitA, int limitB) {
        return State(limitA, y, t+1);
    }

    State fillB(int limitA, int limitB) {
        return State(x, limitB, t+1);
    }

    State emptyA(int limitA, int limitB) {
        return State(0, y, t+1);
    }

    State emptyB(int limitA, int limitB) {
        return State(x, 0, t+1);
    }

    State moveAtoB(int limitA, int limitB) {
        int mov = min(x, limitB - y);
        return State(x - mov, y + mov, t+1);
    }

    State moveBtoA(int limitA, int limitB) {
        int mov = min(y, limitA - x);
        return State(x + mov, y - mov, t+1);
    }


    bool operator==(const State &other) {
        return (x == other.x && y == other.y);
    }
};


class Solver {
private:
    static const int MAXN = 1e5;

    queue<State> q;
    set<int> vis[MAXN + 10];
public:
    int limitA, limitB;
    State x;

    int solve(State target);
};

int Solver::solve(State target) {
    q.push(x);
    vis[x.x].insert(x.y);


    while(!q.empty()) {
        auto st = q.front();
        q.pop();

        if(st == target) {
            return st.t;
        }

        auto nst = State();

        nst = st.emptyA(limitA, limitB);
        if(vis[nst.x].find(nst.y) == vis[nst.x].end()) q.push(nst), vis[nst.x].insert(nst.y);
        nst = st.emptyB(limitA, limitB);
        if(vis[nst.x].find(nst.y) == vis[nst.x].end()) q.push(nst), vis[nst.x].insert(nst.y);
        nst = st.fillA(limitA, limitB);
        if(vis[nst.x].find(nst.y) == vis[nst.x].end()) q.push(nst), vis[nst.x].insert(nst.y);
        nst = st.fillB(limitA, limitB);
        if(vis[nst.x].find(nst.y) == vis[nst.x].end()) q.push(nst), vis[nst.x].insert(nst.y);
        nst = st.moveAtoB(limitA, limitB);
        if(vis[nst.x].find(nst.y) == vis[nst.x].end()) q.push(nst), vis[nst.x].insert(nst.y);
        nst = st.moveBtoA(limitA, limitB);
        if(vis[nst.x].find(nst.y) == vis[nst.x].end()) q.push(nst), vis[nst.x].insert(nst.y);
    }


    return -1;
}


Solver solver;


int main() {
    cin.tie(0) -> sync_with_stdio(false);

    State x;
    cin >> solver.limitA >> solver.limitB;
    cin >> x.x >> x.y;
    cout << solver.solve(x);



    return 0;
}