#include <bits/stdc++.h>



using namespace std;


int a, b, c;
int n;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> a >> b >> c;
    cin >> n;


    int i = 0, j = 0, k = 0;

    for(i=0; i*a + j*b + k*c <= n+1; i++) {
        for(j=0; i*a + j*b + k*c <= n+1; j++) {
            for(k=0; i*a + j*b + k*c <= n+1; k++) {
                // cout << i << " " << j << " " << k << " " << i*a + j*b + k*c << "\n";
                if(i*a + j*b + k*c == n) {
                    cout << 1;
                    return 0;
                }
            }
            k=0;
        }
        j=0;
    }

    cout << 0;


    return 0;
}