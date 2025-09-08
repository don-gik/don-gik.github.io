#include <bits/stdc++.h>



using namespace std;


const int MAXN = 2e5;


struct Node {
    int value;
    int prev;
    int next;
};


int n;
int a[MAXN + 10];

int s[MAXN + 10];
Node x[MAXN + 10];


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for(int i=1; i<n; i++) {
        cin >> a[i];
    }


    for(int i=2; i<n; i++) {
        s[i-1] = (a[i] - a[i-1]) / 2;
    }

    for(int i=1; i<n-1; i++) {
        // cout << s[i] << " ";
    }
    // cout << "\n";


    for(int i=0; i<n; i++) {
        x[i] = {i+1, i-1, i+1};
    }


    int start = 0;
    int end = 0;

    while(start < n-1 && end < n-1) {
        start++;
        end++;

        while(s[start] != 1 && start < n-1) start++;
        while(s[end] != -1 && end < n-1) end++;

        if(start >= end) break;

        // cout << start << " " << end << "\n";

        x[x[end].prev].next = x[end].next;
        x[x[end].next].prev = x[end].prev;
        x[x[start].prev].next = end;
        x[end].prev = x[start].prev;
        x[end].next = start;
        x[start].prev = end;
    }

    int ind = 0;
    while(ind <= n-1) {
        cout << x[ind].value << " ";

        ind = x[ind].next;
    }



    return 0;
}