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
int flag[Nmax];
string ans;
int res;
inline int get_res()
{
    int res=0;
            for(int j=0;j<p;j++)
            {
                for(int k=1;k<=n;k++)
                {
                    if(s[k][j]!=ans[j])
                        res++;
                }
            }
            return res;
}
void dfs(int pos,int k)
{
    if(pos == k)
    {
        //cout<<ans<<endl;
        if(check(ans))
        {
            res=min(res,get_res());
        }

        return;
    }
    for(int i=0;i<=1;i++)
    {
        ans[pos]=i+'0';
        dfs(pos+1,k);
    }
    return;
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
        flag[i]=0;
        for(int j=1;j<=n;j++)
        {
            if(s[j][i]=='1')
                a[i]++;
        }
    }
    ans="";
    for(int i=0;i<p;i++)
        ans+='0';

    res=2147483647;
    dfs(0,p);
    cout<<res<<endl;
    //for(int i=0;i<p;i++)
        //cout<<pii[i].first<<" "<<pii[i].second<<endl;


    return 0;
}
