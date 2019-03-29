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

//��֪������������������ 
//parm:{in,len:inorder�п�ʼ��λ��,�Լ����� af:afterorder�п�ʼ��λ�ã�����ǰnode��valueֵ} 
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
	//����������в��ҵ�ǰ���λ�� 
	for(index=0;index<len;index++)
	{
		if(inorder[in+index]==afterorder[af])
			break;
	}
	node->lson=BinaryTreeOrderings1(af-index-1,in,index);//���Ϊ������ 
	node->rson=BinaryTreeOrderings1(af-1,in+index+1,len-(index+1));//�ұ�Ϊ������ 
	return node;
}

//��֪������������������
//parm:{in,len:inorder�п�ʼ��λ��,�Լ����� pre:preorder�п�ʼ��λ�ã�����ǰnode��valueֵ} 
Node* BinaryTreeOrderings2(int in,int pre,int len)
{
	if(len<=0)
		return NULL;
	if((in>=n)||(in<0))
		return NULL;
	if((pre>=n)||(pre<0))
		return NULL;
	int index=0;
	//����������в��ҵ�ǰ���λ�� 
	for(index=0;index<len;index++)
	{
		if(inorder[in+index]==preorder[pre])
			break;
	}
	Node* node=new Node();
	node->value=preorder[pre];
	node->lson=BinaryTreeOrderings2(in,pre+1,index);//ǰ��Ϊ������ 
	node->rson=BinaryTreeOrderings2(in+index+1,pre+index+1,len-index-1);//����Ϊ������	
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
