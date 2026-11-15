#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode* Tree;
struct TreeNode{
    int v;
    Tree left,right;
};

Tree create()
{
    Tree T;
    T=(Tree)malloc(sizeof(struct TreeNode));
    if(!T) return NULL;
    T->v=0;
    T->left=NULL;
    T->right=NULL;
    return T;
}

void record(int *arr,int n)
{
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
}

int find(int v,int* arr,int front,int rear)
{
    for(int i=front;i<rear;i++){
        if(arr[i]==v) return i;
    }
    return -1;//没找到
}

Tree build(int p_front,int p_rear,int i_front,int i_rear,int *pre,int *in)
{
    if(p_front>=p_rear || i_front>=i_rear) return NULL;
    int t=pre[p_front];
    int sep=find(t,in,i_front,i_rear);
    if(sep==-1) return NULL;
    Tree T=create();
    T->v=t;
    int leftLen=sep-i_front;
    T->left=build(p_front+1,p_front+1+leftLen,i_front,sep,pre,in);
    T->right=build(p_front+1+leftLen,p_rear,sep+1,i_rear,pre,in);
    return T;
}

void post(Tree T)
{
    if(!T) return;
    post(T->left);
    post(T->right);
    printf(" %d",T->v);
    return;
}

void Free(Tree T)
{
    if(!T) return;
    Free(T->left);
    Free(T->right);
    free(T);
    return;
}

int main()
{
    int n;
    int *pre,*in;
    Tree T;

    scanf("%d",&n);
    pre=(int*)malloc(n*sizeof(int));
    in=(int*)malloc(n*sizeof(int));
    if(!pre || !in) return 1;
    record(pre,n);
    record(in,n);
    T=build(0,n,0,n,pre,in);
    post(T);
    Free(T);
    free(pre);
    free(in);
    return 0;
}