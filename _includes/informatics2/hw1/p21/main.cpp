#include <bits/stdc++.h>
using namespace std;int c[30],i,a,b;int main(){iota(c,c+20,1);for(i=0;i<10;i++){cin>>a>>b;reverse(c+a-1,c+b);}for(i=0;i<20;i++)cout<<c[i]<<" ";}