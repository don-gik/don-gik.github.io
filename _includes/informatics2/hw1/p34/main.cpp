#include <bits/stdc++.h>


using namespace std;

typedef long long ll;


const int MAXN = 5e5;

int n;
int v[MAXN + 10] = {};
int dp[MAXN + 10] = {};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for(int i=0; i<n; i++) cin >> v[i];

    ll sum = 1;
    dp[n-1] = 1;
    for(int i=n-2; i>=0; i--) {
        dp[i] = min(dp[i+1]+1, v[i]);
        sum += dp[i];
        // cout << dp[i] << " ";
    }
    // cout << "\n";


    cout << sum;


    return 0;
}