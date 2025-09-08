#include <bits/stdc++.h>



using namespace std;


int n;
int res = 0;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;

    for(int i=1; i<=n; i++) {
        int c = 0;
        int ind = i;

        while(ind > 0) { c += ind % 10; ind /= 10; }

        res += (i % c == 0);
    }

    cout << res;


    return 0;
}