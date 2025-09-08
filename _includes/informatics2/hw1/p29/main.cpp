#include <bits/stdc++.h>



using namespace std;


const int MAXN = 1024;

int k;

struct Paper {
    int w = 2;
    int h = 2;
    int m[MAXN + 10][MAXN + 10] = {};

    void R(void) {
        for(int i=0; i<w; i++) {
            for(int j=0; j<h; j++) {
                m[i + w][j] = m[i][j];
            }
        }

        for(int i=0; i<w; i++) {
            for(int j=0; j<h; j++) {
                m[w - i - 1][j] = m[i + w][j];
            }
        }

        w *= 2;

        return;
    }

    void L(void) {
        for(int i=0; i<w; i++) {
            for(int j=0; j<h; j++) {
                m[w * 2 - i - 1][j] = m[i][j];
            }
        }

        w *= 2;

        return;
    }

    void D(void) {
        for(int i=0; i<w; i++) {
            for(int j=0; j<h; j++) {
                m[i][j + h] = m[i][j];
            }
        }

        for(int i=0; i<w; i++) {
            for(int j=0; j<h; j++) {
                m[i][h - j - 1] = m[i][j + h];
            }
        }

        h *= 2;

        return;
    }

    void U(void) {
        for(int i=0; i<w; i++) {
            for(int j=0; j<h; j++) {
                m[i][h * 2 - j - 1] = m[i][j];
            }
        }

        h *= 2;

        return;
    }
};


Paper p;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> k;

    p.m[0][0] = 0;
    p.m[0][1] = 2;
    p.m[1][0] = 1;
    p.m[1][1] = 3;

    string str;
    for(int i=0; i<k * 2; i++) {
        cin >> str[i];
    }

    for(int i=k*2; i>0; i--) {
        char c = str[i-1];

        if(c == 'R') p.R();
        if(c == 'L') p.L();
        if(c == 'D') p.D();
        if(c == 'U') p.U();
    }

    // for(int i=0; i<p.h; i++) {
    //     for(int j=0; j<p.w; j++) {
    //         cout << p.m[i][j] << " ";
    //     }
    //     cout << "\n";
    // }


    int h;
    cin >> h;

    for(int y=0; y<p.h; y+=2) {
        for(int x=0; x<p.w; x+=2) {
            if(p.m[x][y] == h) cout << 0 << " ";
            if(p.m[x+1][y] == h) cout << 1 << " ";
            if(p.m[x][y+1] == h) cout << 2 << " ";
            if(p.m[x+1][y+1] == h) cout << 3 << " ";
        }
        cout << "\n";
    }


    return 0;
}