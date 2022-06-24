//#define Test
#include<bits/stdc++.h>
using namespace std;
const int Nmax=1000+7;
typedef long long ll;
int n,m,p;
string s[Nmax],t[Nmax];
int main()
{
    #ifdef Test
    #endif
    cin>>n>>m>>p;
    assert(n>=1 && n<=1000);
    assert(m>=1 && m<=1000);
    assert(p>=1 && p<=1000);
    if(p<=10)
        assert(m<=(1<<p)-1);

    for(int i=1;i<=n;i++)
        cin>>s[i];
    for(int j=1;j<=m;j++)
        cin>>t[j];

    sort(t+1,t+1+m);
    for(int i=1;i<m;i++)
        assert(t[i]!=t[i+1]);


    return 0;
}


