#include <bits/stdc++.h>



using namespace std;

int n;

int temp, m;
vector<int> v[2010];


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for(int i = 0; i < 2 * n; i++) {
        cin >> temp;
        v[temp].push_back(i);
    }
    
    for(int i = 1; i <= n; i++) m = max(m, v[i][1] - v[i][0] - 1);
    
    cout << m;
}