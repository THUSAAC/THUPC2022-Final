#include<bits/stdc++.h>
using namespace std;
const int Nmax=1000+7;
typedef long long ll;
int n,m,p;
string s[Nmax],t[Nmax];
int a[Nmax];
int sum[Nmax];
pair<int,int> pii[Nmax];
int check(string ans)
{
    for(int i=1;i<=m;i++)
        if(ans==t[i])
            return 0;
    return 1;
}

int main()
{
    #ifdef Test
    #endif

    cin>>n>>m>>p;
    for(int i=1;i<=n;i++)
        cin>>s[i];
    for(int j=1;j<=m;j++)
        cin>>t[j];

    for(int i=0;i<p;i++)
    {
        a[i]=0;
        for(int j=1;j<=n;j++)
        {
            if(s[j][i]=='1')
                a[i]++;
        }
    }
    
    vector<pair<int,string> > que;
    que.push_back(make_pair(0,""));
    for(int i=0;i<p;i++)
    {
        vector<pair<int,string> > vp;
        vp.clear();
        for(auto c:que)
        {
            vp.push_back(make_pair(c.first+a[i],c.second+'0'));
            vp.push_back(make_pair(c.first+n-a[i],c.second+'1'));
        }
        sort(vp.begin(),vp.end());
        que.resize(min(m+1,(int)vp.size()));
        for(int j=0;j<min(m+1,(int)vp.size());j++)
            que[j]=vp[j];
    }
    for(auto c:que)
    {
        if(check(c.second))
        {
            cout<<c.first<<endl;
            break;
        }
    }
    return 0;
}
