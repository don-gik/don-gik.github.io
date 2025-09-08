#include <bits/stdc++.h>



using namespace std;


const int MAXN = 10;

int n;
int a[MAXN + 10][MAXN + 10];
int b[MAXN + 10][MAXN + 10];

int tempA[MAXN + 10][MAXN + 10];
int tempB[MAXN + 10][MAXN + 10];


int res = 2e9;


void flip(int x) {
    if(x == 0) {
        for(int i=0; i<n; i++) {
            for(int j=0; j<=i; j++) {
                tempA[i][j] = a[i][i-j];
            }
        }
    }else if(x == 1) {
        for(int i=0; i<n; i++) {
            for(int j=0; j<=i; j++) {
                tempA[i][j] = a[n-(i-j)-1][j];
            }
        }
    }else if(x == 2) {
        for(int i=0; i<n; i++) {
            for(int j=0; j<=i; j++) {
                tempA[i][j] = a[n-j-1][n-i-1];
            }
        }
    }
    for(int i=0; i<n; i++) {
        for(int j=0; j<=i; j++) {
            a[i][j] = tempA[i][j];
        }
    }

    return;
}

int error(void) {
    int cnt = 0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<=i; j++) {
            cnt += a[i][j] ^ b[i][j];
        }
    }

    return cnt;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;

    for(int i=0; i<n; i++) {
        for(int j=0; j<=i; j++) {
            cin >> a[i][j];
        }
    }
    for(int i=0; i<n; i++) {
        for(int j=0; j<=i; j++) {
            cin >> b[i][j];
        }
    }

    int cnt = 0;
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            for(int x=0; x<4; x++) {
                for(int y=0; y<4; y++) {
                    flip(i); flip(j);
                    flip(x); flip(y);
                    res = min(res, error());
                    flip(y); flip(x);
                    flip(j); flip(i);
                }
            }
        }
    }


    cout << res;


    return 0;
}