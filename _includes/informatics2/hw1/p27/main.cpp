#include <bits/stdc++.h>



using namespace std;



const int MAXC = 100;

string s, t;
vector<int> c[MAXC + 10];

int turn = 1;
int pos = 0;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> s >> t;
    for(int i=0; i<t.size(); i++) {
        c[t[i] - 96].push_back(i+1);
    }

    for(int i=0; i<s.size(); i++) {
        auto it = lower_bound(c[s[i] - 96].begin(), c[s[i] - 96].end(), pos+1);

        if(it == c[s[i] - 96].end()) turn++, pos = 0;

        it = lower_bound(c[s[i] - 96].begin(), c[s[i] - 96].end(), pos+1);

        if(it == c[s[i] - 96].end()) { cout << -1; return 0; }
        else pos = *it;
    }

    cout << turn;


    return 0;
}