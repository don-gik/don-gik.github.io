#include <bits/stdc++.h>


using namespace std;


struct Point {
    int x;
    int y;

    Point(void) : x(0), y(0) {}
    Point(int X, int Y) : x(X), y(Y) {}

    bool operator==(const Point &other) const {
        return (x == other.x && y == other.y);
    }
};

struct Output {
    string ans;

    Output(string Ans) : ans(Ans) {}
};


class Solver {

private:
    Point a1, a3;
    Point b1, b3;

    void calculate(void);
    bool isPoint(void);
    bool isLine(void);
    bool isFace(void);
    bool isNull(void);

public:
    Point a2, a4;
    Point b2, b4;

    Output solve(void);
};

void Solver::calculate(void) {
    a1 = Point(a4.x, a2.y);
    a3 = Point(a2.x, a4.y);

    b1 = Point(b4.x, b2.y);
    b3 = Point(b2.x, b4.y);

    return;
}

bool Solver::isPoint(void) {
    return (a1 == b3
         || a2 == b4
         || a3 == b1
         || a4 == b2);
}

bool Solver::isLine(void) {
    return (
        (a2.x == b1.x) ||
        (a3.y == b1.y) ||
        (a4.x == b2.x) ||
        (a1.y == b4.y)
    );
}

bool Solver::isFace(void) {
    return !(
        (*this).isPoint() ||
        (*this).isLine() ||
        (*this).isNull()
    );
}

bool Solver::isNull(void) {
    return (
        (a1.y < b3.y) ||
        (a2.x < b1.x) ||
        (a3.y > b1.y) ||
        (a4.x > b2.x)
    );
}

Output Solver::solve(void) {
    (*this).calculate();
    
    if((*this).isPoint()) return Output("POINT");
    if((*this).isNull()) return Output("NULL");
    if((*this).isLine()) return Output("LINE");
    if((*this).isFace()) return Output("FACE");

    return Output("Error");
}


Solver solver;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 

    cin >> solver.a4.x >> solver.a4.y >> solver.a2.x >> solver.a2.y;
    cin >> solver.b4.x >> solver.b4.y >> solver.b2.x >> solver.b2.y;

    cout << solver.solve().ans;


    return 0;
}