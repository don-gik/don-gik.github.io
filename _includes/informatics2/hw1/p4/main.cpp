#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005;
const long long INF = 4e18; // Using a large value for infinity

int n;
string a, b;
long long p1, p3, p5, ppair;

long long dp[MAXN][MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    cin >> a;
    cin >> b;
    cin >> p1 >> p3 >> p5 >> ppair;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {


            if (i > 0) {
                long long cost_h = INF;

                if (a[i - 1] == '0') {
                    cost_h = min(cost_h, dp[i - 1][j]);
                }

                cost_h = min(cost_h, dp[i - 1][j] + p1);
                for(int k=1; k<=3; k++) {
                    if(i - k < 0) break;
                    cost_h = min(cost_h, dp[i - k][j] + p3);
                }
                for(int k=1; k<=5; k++) {
                    if(i - k < 0) break;
                    cost_h = min(cost_h, dp[i - k][j] + p5);
                }
                
                dp[i][j] = min(dp[i][j], cost_h);
            }


            if (j > 0) {
                long long cost_j = INF;

                if (b[j - 1] == '0') {
                    cost_j = min(cost_j, dp[i][j - 1]);
                }

                cost_j = min(cost_j, dp[i][j - 1] + p1);
                for(int k=1; k<=3; k++) {
                    if(j - k < 0) break;
                    cost_j = min(cost_j, dp[i][j - k] + p3);
                }
                for(int k=1; k<=5; k++) {
                    if(j - k < 0) break;
                    cost_j = min(cost_j, dp[i][j - k] + p5);
                }

                dp[i][j] = min(dp[i][j], cost_j);
            }


            if (i == j) {
                for(int k=0; k<=4; k++) {
                    for(int l=0; l<=4; l++) {
                        if(i - k >= 0 && j - l >= 0) {
                            dp[i][j] = min(dp[i][j], dp[i - k][j - l] + ppair);
                        }
                    }
                }
            }


            // cout << dp[i][j] << " ";
        }

        // cout << "\n";
    }

    cout << dp[n][n];

    return 0;
}
