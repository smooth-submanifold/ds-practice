#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode* Tree;
struct TreeNode
{
    int v;
    Tree left,right;
};

typedef struct CircleNode* Circle;
struct CircleNode//环形队列
{
    Tree *arr;
    int front,rear;
    int cap;
    int count;
};

/*二叉树函数*/
Tree createT()
{
    Tree T=(Tree)malloc(sizeof(struct TreeNode));
    if(!T){
        return NULL;//分配错误
    }
    T->v=0;
    T->left=NULL;
    T->right=NULL;
    return T;
}

Tree buildT()
{
    char t=0;

    if(scanf(" %c",&t)!=1) return NULL;
    if(t<'0' || t>'9') return NULL;
    Tree T=createT();
    if(!T) return NULL;
    T->v=t-'0';
    T->left=buildT();
    T->right=buildT();
    return T;
}

void pre(Tree T)
{
    if(!T) return;
    printf(" %d",T->v);
    pre(T->left);
    pre(T->right);
    return;
}

void in(Tree T)
{
    if(!T) return;
    in(T->left);
    printf(" %d",T->v);
    in(T->right);
    return;
}

void post(Tree T)
{
    if(!T) return;
    post(T->left);
    post(T->right);
    printf(" %d",T->v);
    return;
}

int height(Tree T)
{
    int h_l=0,h_r=0;

    if(!T){
        return 0;
    }
    else{
        h_l=height(T->left);
        h_r=height(T->right);
        if(h_l>h_r) return h_l+1;
        else return h_r+1;
    }
}

int leaves(Tree T)
{
    int leaf=0;

    if(!T){
        return 0;
    }
    if(!T->left && !T->right){
        return 1;
    }
    else{
        leaf=leaves(T->left)+leaves(T->right);
        return leaf;
    }
}

int nodes(Tree T)
{
    int n;

    if(!T){
        return 0;
    }
    else{
        n=nodes(T->left)+nodes(T->right);
        return n+1;
    }
}

void FreeT(Tree T)
{
    if(!T) return;
    FreeT(T->left);
    FreeT(T->right);
    free(T);
    return;
}


/*循环队列函数*/
Circle createC(int n)//创建环形队列
{
    Circle C=(Circle)malloc(sizeof(struct CircleNode));
    if(!C){
        printf("creataC:malloc failed\n");
        return NULL;
    }
    C->arr=(Tree *)malloc(n*sizeof(Tree));
    C->front=0;
    C->rear=0;
    C->cap=n;
    C->count=0;
    return C;
}

void enqueue(Circle C,Tree T)//入队
{
    if(!C){
        return;
    }
    if(C->count==C->cap){
        return;
    }
    C->arr[C->rear%C->cap]=T;
    C->rear++;
    C->rear%=C->cap;
    C->count++;
    return;
}

Tree dequeue(Circle C)//出队
{
    Tree out;
    if(!C){
        return NULL;
    }
    if(C->count==0){
        return NULL;
    }
    out=C->arr[C->front];
    C->front++;
    C->front%=C->cap;
    C->count--;
    return out;
}

void size(Circle C)
{
    if(!C){
        printf("size:circle does not exist\n");
        return;
    }
    printf("%d\n",C->count);
    return;
}

void empty(Circle C)
{
    if(!C){
        printf("empty:circle does not exist\n");
        return;
    }
    if(C->count==0){
        printf("YES\n");
    }else{
        printf("NO\n");
    }
    return;
}

void full(Circle C)
{
    if(!C){
        printf("full:circle does not exist\n");
        return;
    }
    if(C->count==C->cap){
        printf("YES\n");
    }else{
       printf("NO\n");
    }
    return;
}

void FreeC(Circle C)
{
    if(!C){
        return;
    }
    free(C->arr);
    free(C);
    return;
}

void LevelPrint(Tree T)
{
    Circle C;
    int levelNo=1;
    C=createC(nodes(T)+2);
    enqueue(C,T);
    while(C->count>0){
        int n=C->count;
        printf("level %d:",levelNo++);
        while(n--){
            Tree t=dequeue(C);
            printf(" %d",t->v);
            if(t->left) enqueue(C,t->left);
            if(t->right) enqueue(C,t->right);
        }
        printf("\n");
    }
    FreeC(C);
}

int main()
{
    Tree T;
    T=buildT();
    LevelPrint(T);
    FreeT(T);
    return 0;
}