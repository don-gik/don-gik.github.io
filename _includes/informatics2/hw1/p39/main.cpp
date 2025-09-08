#include <bits/stdc++.h>



using namespace std;


const int MAXN = 5e2;


int n;
int x[MAXN + 10];

int ans = 0;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for(int i=0; i<n; i++) cin >> x[i];

    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            int space = (x[j] - x[i]) / (j - i);
            int a = x[i] - space * i;

            // cout << "i : " << i << " j : " << j << " space : " << space << " a : " << a << "\n";

            int cnt = 0;
            for(int k=0; k<n; k++) {
                // cout << a + space * k << " ";
                cnt += (a + space * k == x[k]);
            }
            // cout << "\n";

            ans = max(ans, cnt);
        }
    }

    cout << n-ans;


    return 0;
}