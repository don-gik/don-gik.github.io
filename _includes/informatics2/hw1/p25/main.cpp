#include <bits/stdc++.h>


using namespace std;


int n;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;

    cout << (char)(((n + 8) % 12) + 65) << (n + 6) % 10;


    return 0;
}