#include <bits/stdc++.h>



using namespace std;


string str;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> str;

    char last = '\0';
    int ans = 0;
    for(auto c : str) {
        if(c != last) ans += 10;
        else ans += 5;

        last = c;
    }


    cout << ans;


    return 0;
}