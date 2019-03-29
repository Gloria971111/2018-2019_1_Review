#include<iostream>
using namespace std;

typedef struct Node{
	int value;
	Node* lson;
	Node* rson;
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
	cout<<af<<" "<<in<<" "<<len<<"hi\n";
	Node* node;
	node->value=afterorder[af];
	cout<<node->value<<endl;
	int index;
	//在中序遍历中查找当前点的位置 
	for(index=0;index<len;index++)
	{
		if(inorder[in+index]==afterorder[af])
			break;
	}
	node->lson=BinaryTreeOrderings1(af-index-1,in,index);//左边为左子树 
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

int main()
{
	scanf("%d",&n);
	
	int i,j;
	for(i=0;i<n;i++)
		scanf("%d",&afterorder[i]);
	for(i=0;i<n;i++)
		scanf("%d",&inorder[i]);
	cout<<"hhh\n";
	root=BinaryTreeOrderings1(n-1,0,n);
	cout<<"hh\n";
	preordering(root);
	return 0;
}
