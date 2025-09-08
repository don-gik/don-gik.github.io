#include <bits/stdc++.h>



using namespace std;


int n, k;
int used[10][10] = {{}};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> k;
    for(int i=0; i<n; i++) {
        int a, b;
        cin >> a >> b;
        used[a][b]++;
    }

    int cnt = 0;
    for(int i=0; i<=6; i++) {
        for(int j=0; j<2; j++) {
            cnt += (used[j][i] + k - 1) / k;
        }
    }

    cout << cnt;


    return 0;
}