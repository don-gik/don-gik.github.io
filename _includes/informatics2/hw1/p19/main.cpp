#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solver {
private:
    static const int MAXN = 101;
    static const int MAXC = 50; // A reasonable upper bound for coupons
    static const int INF = 1e9;
    
    static const int p1 = 10000;
    static const int p3 = 25000;
    static const int p5 = 37000;

    int dp[MAXN + 10][MAXC + 10];


    void print(void) {
        for(int i=0; i<=n; i++) {
            for(int j=0; j<=5; j++) {
                cout << dp[i][j] << " ";
            }
            cout << "\n";
        }

        return;
    }

    void solve(void) {
        for(int i=0; i <= n; i++) {
            for(int j=0; j <= MAXC; j++) {
                dp[i][j] = INF;
            }
        }
        dp[0][0] = 0;

        for(int i=0; i <= n; i++) {
            for(int j=0; j <= MAXC; j++) {
                if (dp[i][j] == INF) continue;

                if (a[i+1]) {
                    dp[i+1][j] = min(dp[i+1][j], dp[i][j]);
                }

                if(j >= 3) {
                    dp[i+1][j-3] = min(dp[i+1][j-3], dp[i][j]);
                }

                dp[i+1][j] = min(dp[i+1][j], dp[i][j] + p1);
                
                dp[i+3][j+1] = min(dp[i+3][j+1], dp[i][j] + p3);

                dp[i+5][j+2] = min(dp[i+5][j+2], dp[i][j] + p5);
            }
        }
    }

public:
    int n;
    int m;
    bool a[MAXN + 5] = {false};

    int dpValue(void) {
        (*this).solve();
        // (*this).print();

        int minimum = INF;
        for(int i=0; i <= MAXC; i++) {
            minimum = min(minimum, dp[n][i]);
        }
        return minimum;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    Solver solver;
    cin >> solver.n >> solver.m;

    for(int i=0; i<solver.m; ++i) {
        int a;
        cin >> a;
        solver.a[a] = true;
    }

    cout << solver.dpValue();

    return 0;
}
