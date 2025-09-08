#include <bits/stdc++.h>


using namespace std;


int n;
int cnt = 0;


void is3there(int x) {
	if(x == 0) {
		return;
	}

	if(x % 10 == 3 || x % 10 == 6 || x % 10 == 9) {
		cnt++;
	}
	is3there(x / 10);
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n;

	for(int i=1; i<=n; i++) {
		is3there(i);
	}

	cout << cnt;


	return 0;	
}