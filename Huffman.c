#include<stdio.h>
#include<stdlib.h>

struct TreeNode
{
    int w;
    struct TreeNode *left,*right;
};
typedef struct TreeNode *Huff;

struct HeapStruct
{
    Huff *item;
    int size;
    int cap;
};
typedef struct HeapStruct *Heap;

/*---------------堆函数--------------*/
Heap createH(int capasity)
{
    Heap h;
    h=(Heap)malloc(sizeof(struct HeapStruct));
    if(!h) return NULL;
    h->item=(Huff*)malloc((capasity+1)*sizeof(Huff));
    if(!h->item){
        free(h);
        return NULL;
    }
    h->cap=capasity;
    h->size=0;
    return h;
}

int isFull(Heap h)
{
    return h->size==h->cap;
}

int isEmpty(Heap h)
{
    return h->size==0;
}

void FreeH(Heap h)
{
    void FreeT(Huff);
    for(int i=1;i<=h->size;i++){
        if(h->item[i]){
            FreeT(h->item[i]);
        }
    }
    free(h->item);
    free(h);
    return;
}

void arrange(Heap h)
{
    if(!h || h->size<=1) return;
    
    for(int i=h->size/2;i>=1;i--){
        Huff tmp=h->item[i];
        int t=i;
        while(2*t<=h->size){
            int child=2*t;
            if(child+1<=h->size && h->item[child+1]->w<h->item[child]->w){
                child++;
            }
            if(h->item[child]->w>=tmp->w){
                break;
            }
            h->item[t]=h->item[child];
            t=child;
        }
        h->item[t]=tmp;
    }
}

void push(Heap h,Huff v)
{
    if(!h) return;
    if(isFull(h)) return;
    int t=++h->size;
    for(;t>1 && v->w<h->item[t/2]->w;t/=2){
        h->item[t]=h->item[t/2];
    }
    h->item[t]=v;
}

int pop(Heap h,Huff* out)
{
    if(!h || isEmpty(h)) return 1;//堆空
    *out=h->item[1];
    Huff tmp=h->item[h->size];
    int t=1;
    int child;
    for(;2*t<=h->size;t=child){
        child=2*t;
        if(child+1<=h->size && h->item[child+1]->w<h->item[child]->w){
            child++;
        }
        if(h->item[child]->w>=tmp->w){
            break;
        }
        h->item[t]=h->item[child];
    }
    h->item[t]=tmp;
    h->size--;
    return 0;
}

/*---------------树函数--------------*/
Huff createT()
{
    Huff t;
    t=(Huff)malloc(sizeof(struct TreeNode));
    if(!t) return NULL;
    t->w=0;
    t->left=NULL;
    t->right=NULL;
    return t;
}

void FreeT(Huff t)
{
    if(!t) return;
    FreeT(t->left);
    FreeT(t->right);
    free(t);
    return;
}

void input(Heap h)
{
    Huff t;
    int v;
    for(int i=1;i<=h->cap;i++){
        t=createT();
        if(scanf("%d",&v)!=1){
            FreeH(h);
            return;
        }
        t->w=v;
        h->item[i]=t;
    }
    h->size=h->cap;
    return;
}

int buildHuff(Heap h)
{
    Huff t;
    int v,wpl=0;

    if(!h) return 0;
    arrange(h);
    int flag=1;
    while(h->size>1){
        t=createT();
        if(!t){

        }
        pop(h,&t->left);
        pop(h,&t->right);
        v=t->left->w+t->right->w;
        t->w=v;
        wpl+=v;
        if(flag==1){
            printf("%d",v);
            flag=0;
        }else{
            printf(" %d",v);
        }
        push(h,t);
    }
    t=h->item[1];
    printf("\n");
    return wpl;
}

/*---------------主函数--------------*/
int main()
{
    Heap h;
    int n,wsl;

    if(scanf("%d",&n)!=1) return 0;
    if(n<1) return 0;
    h=createH(n);
    input(h);
    wsl=buildHuff(h);
    printf("%d\n",wsl);
    FreeH(h);

    return 0;
}