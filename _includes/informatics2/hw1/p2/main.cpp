#include <bits/stdc++.h>



using namespace std;

typedef long long ll;


const int MAXN = 2e5;

int n, s;
int a[MAXN + 10];
    
ll sum = 0;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> s;
    for(int i=0; i<n; i++) cin >> a[i];

    for(int i=0; i<n; i++) sum += (i >= n/2 ? a[i] : -a[i]);
    sum *= 2;

    cout << (n % 2 ? sum - s : sum + s);


    return 0;
}