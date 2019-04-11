#include<iostream>
using namespace std;
#include<vector>

//https://pintia.cn/problem-sets/994805046380707840/problems/994805070971912192
/*树的结构都离不开递归*/

int num[1005];
vector<int>ans;
typedef struct Node{
	int value;
	Node *lson,*rson;
	Node():lson(NULL),rson(NULL){
	}
}*root;

//type=1 为二叉搜索树 type=2 为镜像树 
bool test(int type,int L,int R)
{
	if(L>=R)
		return true;
	int i,j;
	for(i=L+1;i<=R;i++)
	{
		if(type==1){
			if(num[L]<=num[i])
				break;
		}else{
			if(num[L]>num[i])
				break;
		}
	}
	bool flag=1;
	for(j=i;j<=R;j++){
		if(type==1){
			if(num[j]<num[L]){
				flag=0;
				break;
			}
		}else{
			if(num[j]>=num[L]){
				flag=0;
				break;
			}
		}
	}
	if(flag){
		return test(type,L+1,i-1)&&test(type,i,R);
	}else
		return false;
}

//type=1 为二叉搜索树 type=2 为镜像树
Node* build(int type,int L,int R)
{
	if(L>R)
		return NULL;
	int i;
	for(i=L+1;i<=R;i++)
	{
		if(type==1){
			if(num[L]<=num[i])
				break;
		}else{
			if(num[L]>num[i])
				break;
		}
	}
	Node *p=new Node();
	p->value=num[L];
	p->lson=build(type,L+1,i-1);
	p->rson=build(type,i,R);
	return p;
}

void post_order(Node *p)
{
	if(p!=NULL){
		post_order(p->lson);
		post_order(p->rson);
		ans.push_back(p->value);
	}
}

int main()
{
	int n;
	scanf("%d",&n);
	int i;
	for(i=0;i<n;i++)
		scanf("%d",&num[i]);
	bool flag=0;
	Node* root;
	if(test(1,0,n-1)){
		//cout<<"1YES\n";
		flag=1;
		root=build(1,0,n-1);
	}		
	else if(test(2,0,n-1)){
	//	cout<<"2YES\n";
		flag=1;
		root=build(2,0,n-1);
	}
	if(flag==1){
		printf("YES\n");
		post_order(root);
		//cout<<ans.size()<<endl;
		for(i=0;i<ans.size()-1;i++)
			cout<<ans[i]<<" ";
		cout<<ans[i]<<endl;
		//cout<<endl;
	}
	else
		cout<<"NO\n";
		
	return 0;
}
