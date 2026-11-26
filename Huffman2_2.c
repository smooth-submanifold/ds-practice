#include<stdio.h>
#include<stdlib.h>

struct TreeNode
{
    int w;
    int id;
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
    Huff tmp=h->item[h->size--];
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
    if(h->size>0) h->item[t]=tmp;
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

int input(Heap h,int *weight)
{
    if(!h) return 1;
    h->size=0;
    for(int i=1;i<=h->cap;i++){
        int v;
        if(scanf("%d",&v)!=1){
            FreeH(h);
            return 1;
        }
        Huff t=createT();
        if(!t) return 1;
        t->w=v;
        t->id=i-1;
        weight[i-1]=v;
        h->item[i]=t;
        h->size=i;
    }
    return 0;
}

int buildHuff(Heap h)
{
    if(!h) return -1;
    arrange(h);

    int wpl=0;

    while(h->size>1){
        Huff t=createT();
        if(!t) return -1;
        if(pop(h,&t->left) || pop(h,&t->right)){
            FreeT(t);
            return -1;
        }
        int v=t->left->w+t->right->w;
        t->w=v;
        t->id=-1;
        wpl+=v;
        push(h,t);
    }
    return wpl;
}

/*---------------编码函数--------------*/
void encode(Huff t,int n,char codeOf[][n+1],int deepth,char *code)
{
    (void)n;
    if(!t) return;
    if(!t->left && !t->right){
        if(deepth==0){
            codeOf[t->id][0]='0';
            codeOf[t->id][1]='\0';
            return;
        }
        for(int i=0;i<deepth;i++){
            codeOf[t->id][i]=code[i];
        }
        codeOf[t->id][deepth]='\0';
        return;
    }
    code[deepth]='0';
    encode(t->left,n,codeOf,deepth+1,code);
    code[deepth]='1';
    encode(t->right,n,codeOf,deepth+1,code);
    return;
}

void printCode(Huff t,int n,int *weight)
{
    char codeOf[n][n+1];
    char code[n+1];
    for(int i=0;i<n;i++){
        code[i]='0';
    }
    encode(t,n,codeOf,0,code);
    for(int i=0;i<n;i++){
        printf("%d %s\n",weight[i],codeOf[i]);
    }
    return;
}

/*---------------主函数--------------*/
int main()
{
    Heap h;
    int n,wsl;
    Huff t;

    if(scanf("%d",&n)!=1) return 0;
    if(n<1) return 0;

    int weight[n];

    h=createH(n);
    if(!h) return 1;

    if(input(h,weight)){
        FreeH(h);
        return 1;
    }

    wsl=buildHuff(h);
    if(wsl<0){
        FreeH(h);
        return 1;
    }

    t=h->item[1];
    printCode(t,n,weight);
    printf("WPL:%d\n",wsl);

    FreeH(h);
    return 0;
}