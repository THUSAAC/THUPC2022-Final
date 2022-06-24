//#define Test
#include<bits/stdc++.h>
using namespace std;
const int Nmax=1e6+7;
typedef long long ll;
int ran()
{
    return 1000;
    return rand()%1000+1;
}
int main()
{
    #ifdef Test
    #endif
    srand(time(0)); 
    //int T=10;
    //cout<<T<<endl;
//for(int TT=1;TT<=T;TT++)
//{

    int n=ran(),m=ran(),p=ran();
    p=10;

    m=min(m,1000);
    if(p<=10)
        m=min(m,(1<<p)-1);

    cout<<n<<" "<<m<<" "<<p<<endl;
    string s;
    for(int i=1;i<=n;i++)
    {
        s="";
        for(int j=0;j<p;j++)
        {
            int now=rand()%2;
            if(now)
                s+='1';
            else
                s+='0';
        }
        cout<<s<<endl;

    }
    set<string> st;
    for(int i=1;i<=m;i++)
    {
        s="";
        for(int j=0;j<p;j++)
        {
            int now=rand()%2;
            if(now)
                s+='1';
            else
                s+='0';
        }
        if(st.find(s)!=st.end())
        {
            i--;
        }
        else
        {
            st.insert(s);
            cout<<s<<endl;
        }

    }
//}
    return 0;
}


