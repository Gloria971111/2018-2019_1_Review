#include<iostream>
using namespace std;
#include<queue>

//https://pintia.cn/problem-sets/994805046380707840/problems/994805069361299456
typedef struct Node{
	int value;
	Node* lson;
	Node* rson;
	int step; 
	Node(){
		lson=NULL;
		rson=NULL;
	}
};

int afterorder[35];
int inorder[35];
int preorder[35]; 
Node* root;
int n;

//已知后序和中序遍历，建树 
//parm:{in,len:inorder中开始的位置,以及长度 af:afterorder中开始的位置，即当前node的value值} 
Node* BinaryTreeOrderings1(int af,int in,int len)
{
	if(len<=0)
		return NULL;
	if((in>=n)||(in<0))
		return NULL;
	if((af>=n)||(af<0))
		return NULL;
	Node* node=new Node(); //声明指针的时候一定要记得new这个变量 
	node->value=afterorder[af];
	int index;
	//在中序遍历中查找当前点的位置 
	for(index=0;index<len;index++)
	{
		if(inorder[in+index]==afterorder[af])
			break;
	}
	
	node->lson=BinaryTreeOrderings1(af-len+index,in,index);//左边为左子树 	
	node->rson=BinaryTreeOrderings1(af-1,in+index+1,len-(index+1));//右边为右子树 
	return node;
}

//已知先序和中序遍历，建树
//parm:{in,len:inorder中开始的位置,以及长度 pre:preorder中开始的位置，即当前node的value值} 
Node* BinaryTreeOrderings2(int in,int pre,int len)
{
	if(len<=0)
		return NULL;
	if((in>=n)||(in<0))
		return NULL;
	if((pre>=n)||(pre<0))
		return NULL;
	int index=0;
	//在中序遍历中查找当前点的位置 
	for(index=0;index<len;index++)
	{
		if(inorder[in+index]==preorder[pre])
			break;
	}
	Node* node=new Node();
	node->value=preorder[pre];
	node->lson=BinaryTreeOrderings2(in,pre+1,index);//前面为左子树 
	node->rson=BinaryTreeOrderings2(in+index+1,pre+index+1,len-index-1);//后面为右子树	
	return node;
}

void preordering(Node* root)
{
	if(root!=NULL){
		cout<<root->value;
		preordering(root->lson);
		preordering(root->rson);
	}
}

void afterordering(Node* root)
{
	if(root!=NULL){		
		afterordering(root->lson);
		afterordering(root->rson);
		cout<<root->value;
	}
}
int ans[35];
int num=0;

void Cengordering(Node* root)
{
	queue<Node*>q;
	q.push(root);
	while(!q.empty())
	{
		Node* now=q.front();
		q.pop();
		if(now->lson!=NULL)
			q.push(now->lson);
		if(now->rson!=NULL)
			q.push(now->rson);
		ans[num]=now->value;
		num++;
	}
	for(int i=0;i<num-1;i++)
		cout<<ans[i]<<" ";
	cout<<ans[num-1]<<endl;
}

int main()
{
	scanf("%d",&n);
	
	int i,j;
	for(i=0;i<n;i++)
		scanf("%d",&afterorder[i]);
//	for(i=0;i<n;i++)
//		scanf("%d",&preorder[i]);
	for(i=0;i<n;i++)
		scanf("%d",&inorder[i]);
	//cout<<"hhh\n";
	
	//建立 
	root=BinaryTreeOrderings1(n-1,0,n);
	//preordering(root);
	Cengordering(root);
//	root=BinaryTreeOrderings2(0,0,n);
//	afterordering(root);
	return 0;
}
