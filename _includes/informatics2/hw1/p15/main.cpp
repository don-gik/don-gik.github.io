#include <bits/stdc++.h>



using namespace std;

int n, a, b, t1, t2;

vector<int> A, B, c1, c2;



int main() {
    cin >> n;
    
    for(int l=0; l<n; l++) {
        cin >> t1;
        while(t1--) { cin >> t2; A.push_back(t2); }

        cin >> t1;
        while(t1--) { cin >> t2; B.push_back(t2); }
        
        for(int i=4; i>0; i--) {
            c1.push_back(count(A.begin(), A.end(), i));
            c2.push_back(count(B.begin(), B.end(), i));
        }
        
        for(int i=0; i<4; i++) {
            if(c1[i] != c2[i]) {
                cout << (c1[i] > c2[i] ? 'A' : 'B') << '\n';
                break;
            }
            if(i == 3) cout << 'D' << '\n';
        }
        
        A.clear();
        B.clear();
        c1.clear();
        c2.clear();
    }
}