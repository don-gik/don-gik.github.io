#include <bits/stdc++.h>



using namespace std;


int n, k;
vector<int> v;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> k;
    for(int i=0; i<n; i++) {
        int a;
        cin >> a;

        v.push_back(a);
    }


    nth_element(v.begin(), v.begin() + k, v.end(), [&](const int &a, const int &b) {
        return a > b;
    });


    cout << accumulate(v.begin(), v.begin() + k, 0) - (k * (k-1) / 2);



    return 0;
}