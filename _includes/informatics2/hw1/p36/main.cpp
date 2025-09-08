#include <bits/stdc++.h>



using namespace std;


const int MAXN = 2500;

int n, k, p;
int a[MAXN + 10];

int res;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> k >> p;
    for(int i=0; i<n*k; i++) cin >> a[i];

    for(int i=0; i<n*k; i+=k) {
        int cnt = 0;
        for(int j=0; j<k; j++) cnt += 1 - a[i+j];

        if(cnt < p) res++;
    }

    cout << res;


    return 0;
}