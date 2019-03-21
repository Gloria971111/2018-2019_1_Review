#include<iostream>
using namespace std;
#include<stack>

const int maxn=505;
const int INF=0X3f3f3f;
int person[maxn];

bool vis[maxn];
int pre[maxn];
int cost[maxn][maxn];
int lowcost[maxn];

int lowpathnum=0;
int lowpre[maxn];
stack<int>path;

//dijkstra˼�룺���ҳ���ǰ���е��е�Դ�������С�ĵ㣬���Դ�Ϊ"���ݵ�" ������
//"��ɢ"���жϲ��޸���֮��صĵ㣬ʱ�临�Ӷ�ΪO��n^2�� 
void dijkstra(int cost[maxn][maxn],int lowcost[],int n,int beg)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		pre[i]=-1;
		vis[i]=false;
		lowcost[i]=INF;
	}
	lowcost[beg]=0;
	for(i=0;i<n;i++)
	{
		int k=-1;
		int Min=INF;
		for(j=0;j<n;j++)
		{
			if(!vis[j]&&lowcost[j]<Min)
			{
				Min=lowcost[j];
				k=j;
			}
		}//Ѱ�ҵ�ǰ����Դ������ĵ�
		if(k==-1)
			break;//���е㶼��ȷ����̾��� 
		vis[k]=true;//��ǰ����ȷ����̾���
		
		for(j=0;j<n;j++) //������������С����صĵ�ľ��� 
		{
			if(!vis[j]&&((cost[j][k]+lowcost[k])<lowcost[j]))
			{
				lowcost[j]=cost[j][k]+lowcost[k];
				pre[j]=k;
			} 
		}
	}
}

int main()
{
	int n,m,s,d;
	scanf("%d%d%d%d",&n,&m,&s,&d);
	int i,j;
	for(i=0;i<n;i++)
		scanf("%d",&person[i]);
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			cost[i][j]=INF;
	for(i=0;i<m;i++)
	{
		int u,v,c;
		scanf("%d%d%d",&u,&v,&c);
		cost[u][v]=c;
		cost[v][u]=c;
	}
	dijkstra(cost,lowcost,n,s);
//	for(i=0;i<n;i++)
//		cout<<lowcost[i]<<" ";
//	cout<<endl;
	
	for(i=0;i<n;i++)
	{
		if(i!=d)
		{
			if((lowcost[i]+cost[i][d])==lowcost[d])
			{
				lowpre[lowpathnum]=i;
				lowpathnum++;
			}
		}		
	}
	if(s==d)
	{
		cout<<"1"<<" "<<person[d]<<endl;
		cout<<s<<endl;
		return 0;
	}
	cout<<lowpathnum<<" ";
	int maxsum=0;
	int maxpre=0;
	for(i=0;i<lowpathnum;i++)
	{
		int nowpre=lowpre[i];
		int sum=0;
		while(nowpre!=-1)
		{
			sum=sum+person[nowpre];
			nowpre=pre[nowpre];
		}
		if(maxsum<sum)
		{
			maxsum=sum;
			maxpre=lowpre[i];
		}
	}
	cout<<maxsum+person[d]<<endl;
	while(maxpre!=s)
	{
		path.push(maxpre);
		maxpre=pre[maxpre];
	} 
	path.push(s);
	while(!path.empty())
	{
		cout<<path.top()<<" ";
		path.pop();
	}
	cout<<d<<endl;
	return 0;
}
