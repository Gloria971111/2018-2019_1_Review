#include<iostream>
using namespace std;
#include<algorithm> 

//https://pintia.cn/problem-sets/994805046380707840/problems/994805068539215872
/*并查集关键：find join函数 father数组*/ 

typedef struct Node{
	int num;
	int fa,mo;
	int k;
	int children[6];
	int housenum=0;
	int housesq=0;
}; 

typedef struct Root{
	int num;
	int people=0;
	int minnum=10000;
	double avehousenum=0;
	double avehousesq=0;
};

int father[10000];
Node node[10000];
Root root[10000];
int totalpeople=0;

int find(int son)
{
	//int reu=son;
	while(father[son]!=son)
		son=father[son];
	return son;
}

void join(int a,int b)
{
	int fa=find(a);
	int fb=find(b);
	if(fa!=fb)
	{
		father[fb]=fa;
	}
}

void Merge(int son,int fa,int mo)
{
	if((fa==-1)&&(mo==-1))
		return;
	if(fa==-1)
	{
		join(mo,son);
		node[mo].num=mo;
		node[son].num=son;
		return;
	}
	if(mo==-1)
	{
		join(fa,son);
		node[fa].num=fa;
		node[son].num=son;
		return;
	}
	join(fa,son);
	join(fa,mo);
	node[fa].num=fa;
	node[son].num=son;
	node[mo].num=mo;
	return;
}

bool cmp(Node &a,Node &b)
{
	return a.num>b.num;
}

bool cmp2(Root &a,Root &b)
{
	return a.num>b.num;
}

bool cmp3(Root &a,Root &b)
{
	if(a.avehousesq==b.avehousesq)
		return a.minnum<b.minnum;
	return a.avehousesq>b.avehousesq;
}

int main()
{
	int n;
	scanf("%d",&n);
	int i;
	for(i=0;i<10000;i++)
	{
		father[i]=i;
		node[i].num=-1;
		root[i].num=-1;
	}
	for(i=0;i<n;i++)
	{
		int No;
		scanf("%d",&No);
		node[No].num=No;
		scanf("%d%d%d",&node[No].fa,&node[No].mo,&node[No].k);
		Merge(No,node[No].fa,node[No].mo); 
		for(int j=0;j<node[No].k;j++)
		{
			scanf("%d",&node[No].children[j]);
			node[node[No].children[j]].num=node[No].children[j];
			join(No,node[No].children[j]);
		}
		scanf("%d%d",&node[No].housenum,&node[No].housesq);	
	}
	sort(node,node+10000,cmp);
	//cout<<endl;
	int family=0;
	for(i=0;;i++)
	{		
		if(node[i].num==-1)
			break;
		totalpeople++;
	}
	//cout<<totalpeople<<endl;
	for(i=0;i<totalpeople;i++)
	{
		//cout<<node[i].num<<" "<<node[i].fa<<" "<<node[i].mo<<" "<<father[node[i].num]<<" "<<find(node[i].num)<<endl;
		int r=find(node[i].num);
		if(root[r].num==-1)
		{
			family++;
			root[r].num=r;
			root[r].people++;
		}
		else
			root[r].people++;
		root[r].avehousenum+=node[i].housenum;
		root[r].avehousesq+=node[i].housesq;
		if(root[r].minnum>node[i].num)
			root[r].minnum=node[i].num;
		
	}
	sort(root,root+10000,cmp2);
	for(i=0;i<family;i++)
	{
		root[i].avehousenum=root[i].avehousenum/(double)root[i].people;
		root[i].avehousesq=root[i].avehousesq/(double)root[i].people;
	}	
	cout<<family<<endl; 
	sort(root,root+family,cmp3);
	for(i=0;i<family;i++)
		printf("%04d %d %.3lf %.3lf\n",root[i].minnum,root[i].people,root[i].avehousenum,root[i].avehousesq);
		
	return 0;
} 
