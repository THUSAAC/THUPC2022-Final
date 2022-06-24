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
int dfs(int pos,int k)
{
    if(pos == k+1)
    {
        for(int i=0;i<p;i++)
        {
            if(flag[i])
            {
                if(ans[pii[i].second]=='1')
                    ans[pii[i].second]='0';
                else ans[pii[i].second]='1';
            }
        }

        if(check(ans))
            return 1;

        for(int i=0;i<p;i++)
        {
            if(flag[i])
            {
                if(ans[pii[i].second]=='1')
                    ans[pii[i].second]='0';
                else ans[pii[i].second]='1';
            }
        }
        return 0;
    }
    for(int i=0;i<p;i++)
    {
        if(!flag[i])
        {
            flag[i]=1;
            if(dfs(pos+1,k))
                return 1;
            flag[i]=0;
        }
    }
    return 0;
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
    for(int i=0;i<p;i++)
    {
        if(a[i]>n-a[i])
        {
            ans[i]='1';
        }
        else ans[i]='0';
        //sum[i]=max(a[i],n-a[i]);
        sum[i]=abs(n-2*a[i]);
        pii[i].first=sum[i];
        pii[i].second=i;
    }
    sort(pii,pii+p);
    //cout<<ans<<endl;
    if(check(ans))
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
        //cout<<ans<<endl;
        cout<<res<<endl;
        return 0;
    }
    for(int i=1;i<=p;i++)
    {
        if(dfs(1,i))
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
            //cout<<ans<<endl;
            cout<<res<<endl;
            break;
        }
    }
    //for(int i=0;i<p;i++)
        //cout<<pii[i].first<<" "<<pii[i].second<<endl;


    return 0;
}
