#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define Data int
#define MaxSize 20000

typedef struct HeapStruct
{
    Data *item;
    int size;
} *Heap;

Heap create()
{
    Heap h;
    h=(Heap)malloc(sizeof(struct HeapStruct));
    if(!h) return NULL;
    h->item=(Data*)malloc(MaxSize*sizeof(Data));
    if(!h->item){
        free(h);
        return NULL;
    }
    h->size=0;
    return h;
}

int isFull(Heap h)
{
    return h->size==MaxSize;
}

void Free(Heap h)
{
    free(h->item);;
    free(h);
    return;
}

void arrange(Heap h)
{
    if(!h || h->size<2) return;
    
    for(int i=h->size/2;i>=1;i--){
        Data tmp=h->item[i];
        int t=i;
        while(2*t<=h->size){
            int child=2*t;
            if(child+1<=h->size && h->item[child+1]<h->item[child]){
                child++;
            }
            if(h->item[child]>=tmp){
                break;
            }
            h->item[t]=h->item[child];
            t=child;
        }
        h->item[t]=tmp;
    }
}

Heap heapify(int n)
{
    Heap h=create();
    if(!h) return NULL;
    for(int i=1;i<=n;i++){
        if(scanf("%d",&h->item[i])!=1){
            Free(h);
            return NULL;
        }
    }
    h->size=n;
    arrange(h);
    return h;
}

void push(Heap h,Data v)
{
    if(!h) return;
    if(isFull(h)) return;
    int t=++h->size;
    for(;t>1 && v<h->item[t/2];t/=2){
        h->item[t]=h->item[t/2];
    }
    h->item[t]=v;
}

Data pop(Heap h)
{
    if(!h || h->size==0) return 0;
    Data v=h->item[1];
    Data tmp=h->item[h->size];
    int t=1;
    while(2*t<=h->size){
        int child=2*t;
        if(child+1<=h->size && h->item[child+1]<h->item[child]){
            child++;
        }
        if(h->item[child]>=tmp){
            break;
        }
        h->item[t]=h->item[child];
        t=child;
    }
    h->item[t]=tmp;
    h->size--;
    return v;
}

void printHeap(Heap h)
{
    if(!h || h->size==0) return;
    printf("%d",h->item[1]);
    if(h->size==1){
        printf("\n");
        return;
    }
    for(int i=2;i<=h->size;i++){
        printf(" %d",h->item[i]);
    }
    printf("\n");
    return;
}

void test(Heap h)
{
    for(int i=0;i<10000;i++){
        push(h,i);
    }
    for(int i=0;i<10000;i++){
        pop(h);
    }
    printHeap(h);
    return;
}

int main()
{
    Heap h;
    int n,m;
    char oper[10];
    Data v;

    if(scanf("%d",&n)!=1) return 0;
    h=heapify(n);
    if(scanf("%d",&m)!=1){
        Free(h);
        return 0;
    }
    while(m--){
        scanf("%s",oper);
        if(strcmp(oper,"push")==0){
            if(scanf("%d",&v)!=1){
                Free(h);
                return 0;
            }
            push(h,v);
        }else if(strcmp(oper,"pop")==0){
            if(!h) break;
            v=pop(h);
            printf("%d\n",v);
        }else if(strcmp(oper,"print")==0){
            printHeap(h);
        }
    }
    
    // test(h);
    Free(h);
    return 0;
}