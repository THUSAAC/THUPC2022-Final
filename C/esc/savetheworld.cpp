#include<cstdio>
#include<cassert>
#include<algorithm>
#define cmin(a,b) (a>(b)?a=(b),1:0)
#define cmax(a,b) (a<(b)?a=(b),1:0)
#define dmin(a,b) ((a)<(b)?(a):(b))
#define dmax(a,b) ((a)>(b)?(a):(b))
namespace io
{
	int F()
	{
		int n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
	long long G()
	{
		long long n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
}
int a[1111][1111],x[1111111],y[1111111];
int x1[2222222],y1[2222222],x2[2222222],y2[2222222];
int k;
void swp(int X1,int Y1, int X2, int Y2)
{
	assert(X1==X2||Y1==Y2);
	int d1=a[X1][Y1];
	int d2=a[X2][Y2];
	x[d1]=X2;
	x[d2]=X1;
	y[d1]=Y2;
	y[d2]=Y1;
	std::swap(a[X1][Y1],a[X2][Y2]);
	x1[++k]=X1;
	x2[k]=X2;
	y1[k]=Y1;
	y2[k]=Y2;
}
int deg[1111],q[1111],hq,tq;
int main()
{
	int n=io::F();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			a[i][j]=io::F();
			x[a[i][j]]=i;
			y[a[i][j]]=j;
		}
	for(int i=1;i<=n;++i)
	{
		if(i!=n)
		{
			for(int j=1;j<=n;++j)
				deg[j]=0;
			for(int j=1;j<=n;++j)
			{
				int now=(i-1)*n+j;
				deg[y[now]]++;
			}
			hq=tq=0;
			for(int j=1;j<=n;++j)
				if(deg[j]==0)q[tq++]=j;
			for(;hq!=tq;++hq)
			{
				int now=(i-1)*n+q[hq];
				if(--deg[y[now]]==0)q[tq++]=y[now];
				swp(x[now],y[now],x[now],q[hq]);
				if(x[now]!=i)swp(i,y[now],x[now],y[now]);
			}
			for(int j=1;j<=n;++j)
			{
				int now=(i-1)*n+j;
				if(x[now]!=i)swp(x[now],y[now],i,y[now]);
			}
		}
		for(int j=1;j<n;++j)
		{
			int now=(i-1)*n+j;
			if(y[now]!=j)swp(x[now],y[now],x[now],j);
		}
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			assert(a[i][j]==(i-1)*n+j);
	printf("%d\n",k);
	for(int i=1;i<=k;++i)
		printf("%d %d %d %d\n",x1[i],y1[i],x2[i],y2[i]);
	return 0;
}