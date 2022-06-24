//You can include .h file like testlib.h here
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

FILE *inFile;
FILE *outFile;
FILE *ansFile;
FILE *scoreFile;
FILE *infoFile;
double score;
bool swap_flag;

void ret(double result, const char* info){
	if(swap_flag)
		fprintf(infoFile, "%s\n", info);	//Arbiter only allow to read EXACTLY one line info, no less and no more, and must BEFORE score
	fprintf(scoreFile, "%.6f\n", result * score);
	if(!swap_flag)
		fprintf(infoFile, "%s\n", info);
	exit(0);
}

int a[1111][1111];

int main(int argc, char **argv){
	//You'd better not change this swith block
	switch(argc){
		case 0:		//LOJ
			inFile = fopen("input", "r");
			outFile = fopen("user_out", "r");
			ansFile = fopen("answer", "r");
			scoreFile = stdout;
			infoFile = stderr;
			score = 100;
			break;
		case 4:		//Arbiter
			inFile = fopen(argv[1], "r");
			outFile = fopen(argv[2], "r");
			ansFile = fopen(argv[3], "r");
			scoreFile = infoFile = fopen("/tmp/_eval.score", "w");
			score = 10;
			swap_flag = true;
			break;
		case 5:
			if(strcmp(argv[4], "THUOJ") == 0){	//Tsinghua OJ(OJ for DSA course)
				inFile = fopen(argv[1], "r");
				outFile = fopen(argv[3], "r");
				ansFile = fopen(argv[2], "r");
				scoreFile = stdout;
				infoFile = stdout;
				score = 100;
			}else{								//Tsinsen OJ
				inFile = fopen(argv[1], "r");
				outFile = fopen(argv[2], "r");
				ansFile = fopen(argv[3], "r");
				scoreFile = fopen(argv[4], "w");
				infoFile = fopen("tmp", "w");		//Tsinsen doesn't use this file
				score = 1;
			}
			break;
		case 7:		//Lemon and TUOJ
			inFile = fopen(argv[1], "r");
			outFile = fopen(argv[2], "r");
			ansFile = fopen(argv[3], "r");
			FILE *fs = fopen(argv[4], "r");
			if(fs)
				fscanf(fs, "%lf", &score);		//Current TUOJ
			else
				sscanf(argv[4], "%lf", &score);	//Lemon and future TUOJ
			scoreFile = fopen(argv[5], "w");
			infoFile = fopen(argv[6], "w");
			break;
	}
	int n,k;
	if(fscanf(outFile, "%d", &k) != 1)
		ret(0, "Can\'t read the integer.");
	
	fscanf(inFile,"%d",&n);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			fscanf(inFile,"%d",&a[i][j]);
	
	if(k<0||k>2*n*n-2*n)
		ret(0, "Invalid k.");
	
	for(int i=1;i<=k;++i)
	{
		int x,y,x2,y2;
		if(fscanf(outFile,"%d %d %d %d",&x,&y,&x2,&y2)!=4)
			ret(0,"Can't read the integer.");
		if(x!=x2&&y!=y2)
			ret(0,"Invalid move.");
		if(x<1||x>n||y<1||y>n||x2<1||x2>n||y2<1||y2>n)
			ret(0,"Invalid move.");
		std::swap(a[x][y],a[x2][y2]);
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(a[i][j]!=(i-1)*n+j)
				ret(0,"Wrong Answer.");
	ret(1,"Accepted.");
	return 0;
}
