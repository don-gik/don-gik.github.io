#include <bits/stdc++.h>



using namespace std;


const int MAXN = 3e5;

int n;
int a[MAXN + 10];

int res;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for(int i=1; i<=n; i++) cin >> a[i];


    int cnt = 0;
    int last = 0;
    for(int i=1; i<=n; i++) {
        if(last != a[i] % 2) {
            cnt++;
            last = 1 - last;
        }
    }
    res = max(cnt, res);

    cnt = 0;
    last = 1;
    for(int i=1; i<=n; i++) {
        if(last != a[i] % 2) {
            cnt++;
            last = 1 - last;
        }
    }
    res = max(cnt, res);


    cout << res;



    return 0;
}