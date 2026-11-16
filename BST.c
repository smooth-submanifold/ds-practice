#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode *Tree;
struct TreeNode
{
    int v;
    Tree left,right;
};

typedef struct CircleNode *Circle;
struct CircleNode
{
    Tree* arr;
    int front,rear;
    int cap;
    int count;
};

Tree createT()
{
    Tree T;
    T=(Tree)malloc(sizeof(struct TreeNode));
    if(!T) return NULL;
    T->v=0;
    T->left=NULL;
    T->right=NULL;
    return T;
}

void FreeT(Tree T)
{
    if(!T) return ;
    FreeT(T->left);
    FreeT(T->right);
    free(T);
}

void pre_print(Tree T)
{
    if(!T) return;
    printf("%d ",T->v);
    pre_print(T->left);
    pre_print(T->right);
    return;
}

void post_print(Tree T)
{
    if(!T) return;
    post_print(T->left);
    post_print(T->right);
    printf("%d ",T->v);
    return;
}

Circle createC(int n)
{
    Circle C;
    C=(Circle)malloc(sizeof(struct CircleNode));
    if(!C) return NULL;
    C->arr=(Tree *)malloc(n*sizeof(Tree));
    if(!C->arr){
        free(C);
        return NULL;
    }
    C->cap=n;
    C->count=0;
    C->front=0;
    C->rear=0;
    return C;
}

void enqueue(Circle C,Tree T)
{
    if(!C) return ;
    if(C->count==C->cap) return ;
    C->arr[C->rear]=T;
    C->rear=(C->rear+1)%C->cap;
    C->count++;
    return ;
}

Tree dequeue(Circle C)
{
    if(!C) return 0;
    if(C->count==0) return 0;
    Tree out=C->arr[C->front];
    C->front=(C->front+1)%C->cap;
    C->count--;
    return out;
}

void FreeC(Circle C)
{
    if(!C) return ;
    free(C->arr);
    free(C);
    return ;
}

Tree build_level(int node)
{
    char ch;
    scanf(" %c",&ch);
    if(ch<'0' || ch>'9') return NULL;
    Tree T,t;
    T=createT();
    Circle C;
    C=createC(node+1);
    node--;
    T->v=(int)(ch-'0');
    enqueue(C,T);
    while(node>0){
        t=dequeue(C);
        scanf(" %c",&ch);
        if(ch>='0' && ch<='9'){
            t->left=createT();
            t->left->v=(int)(ch-'0');
            enqueue(C,t->left);
        }
        scanf(" %c",&ch);
        if(ch>='0' && ch<='9'){
            t->right=createT();
            t->right->v=(int)(ch-'0');
            enqueue(C,t->right);
        }
        node-=2;
    }
    FreeC(C);
    return T;
}

int JudgeBST(Tree T,int *prev,int *hasPrev)
{
    if(!T) return 1;
    if(!JudgeBST(T->left,prev,hasPrev)) return 0;

    if(*hasPrev && *prev>=T->v) return 0;
    *prev=T->v;
    *hasPrev=1;

    return JudgeBST(T->right,prev,hasPrev);
}

int main()
{
    Tree T;
    int n;
    int prev=0, has=0;

    scanf("%d",&n);
    T=build_level(n);
    printf("%s\n",JudgeBST(T,&prev,&has) ? "YES" : "NO");
    FreeT(T);
    return 0;
}