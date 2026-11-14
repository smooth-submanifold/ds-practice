#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode* Tree;
struct TreeNode
{
    int v;
    Tree left,right;
};

Tree create()
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

Tree build()
{
    char t=0;

    if(scanf(" %c",&t)!=1) return NULL;
    if(t<'0' || t>'9') return NULL;
    Tree T=create();
    if(!T) return NULL;
    T->v=t-'0';
    T->left=build();
    T->right=build();
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
    Tree T;
    T=build();
    printf("pre:");pre(T);printf("\n");
    printf("in:");in(T);printf("\n");
    printf("post:");post(T);printf("\n");
    printf("height: %d\n",height(T));
    printf("leaves: %d\n",leaves(T));
    printf("nodes: %d\n",nodes(T));
    Free(T);
    return 0;
}