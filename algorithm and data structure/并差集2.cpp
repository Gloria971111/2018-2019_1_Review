#include<iostream>
using namespace std;
#include<string.h>

//https://pintia.cn/problem-sets/994805046380707840/problems/994805066135879680

int father[105];

int find(int a)
{
	while(father[a]!=a)
		a=father[a];
	return a;
}

void join(int a,int b)
{
	int fa=find(a);
	int fb=find(b);
	if(fa!=fb)
	{
		father[fa]=fb;
	}
}

int attack[105][105];

int main()
{
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	memset(attack,0,sizeof(attack));
	int i;
	for(i=0;i<105;i++)
		father[i]=i;
	for(i=0;i<m;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		if(c==-1)
		{
			attack[a][b]=attack[b][a]=-1;
		}else
			join(a,b);
	}
	
	for(i=0;i<k;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		int flag1=0,flag2=0;
		if(find(x)==find(y))
			flag1=1;
		if(attack[x][y]==-1)
			flag2=1;
		if((flag1==1)&&(flag2==0))
			cout<<"No problem\n";
		if((flag1==0)&&(flag2==0))
			cout<<"OK\n";
		if((flag1==1)&&(flag2==1))
			cout<<"OK but...\n";
		if((flag1==0)&&(flag2==1))
			cout<<"No way\n";	
	}
	return 0;
}
