#include<stdio.h>
#include<stdlib.h>

#define Data int

typedef struct HeapStruct
{
    Data *item;
    int size;
    int cap;
} *Heap;

Heap create(int cap)
{
    Heap h;
    h=(Heap)malloc(sizeof(struct HeapStruct));
    if(!h) return NULL;
    h->item=(Data*)malloc((cap+1)*sizeof(Data));
    if(!h->item){
        free(h);
        return NULL;
    }
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

void Free(Heap h)
{
    free(h->item);;
    free(h);
    return;
}

void arrange(Heap h)
{
    if(!h || h->size<=1) return;
    
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

int pop(Heap h,Data* out)
{
    if(!h || isEmpty(h)) return 1;//堆空
    *out=h->item[1];
    Data tmp=h->item[h->size];
    int t=1;
    int child;
    for(;2*t<=h->size;t=child){
        child=2*t;
        if(child+1<=h->size && h->item[child+1]<h->item[child]){
            child++;
        }
        if(h->item[child]>=tmp){
            break;
        }
        h->item[t]=h->item[child];
    }
    h->item[t]=tmp;
    h->size--;
    return 0;
}

int main()
{
    Heap h;
    int n,m;

    
    Free(h);
    return 0;
}