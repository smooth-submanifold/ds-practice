#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Arr *Array;
struct Arr
{
    int *arr;
    int size,cap;
};

Array create(void)
{
    Array A=(Array)malloc(sizeof(struct Arr));
    if(!A){
        printf("create:Allocate failed.\n");
        return NULL;
    }
    A->arr=(int*)malloc(sizeof(int));
    if(!A->arr){
        printf("create:Allocate failed.\n");
        free(A);
        return NULL;
    }
    A->size=0;
    A->cap=1;
    return A;
}

void push(Array A,int num)
{
    if (!A){
        printf("Array does not exist.\n");
        return ;
    }
    if (A->size==A->cap){
        int newcap=A->cap*2;
        int *tmp = realloc(A->arr, newcap * sizeof(int));
        if (!tmp) {
            printf("push:Realloc failed");
            return;
        }
        A->arr=tmp;
        A->cap=newcap;
    }
    A->arr[A->size]=num;
    A->size++;
}

int pop(Array A)
{
    if (!A){
        printf("Array does not exist.\n");
        return 0;
    }
    if(A->size==0){
        printf("pop:Element does not exist.\n");
        return 0;
    }
    int v=A->arr[A->size-1];
    A->size--;
    if (4*A->size<=A->cap && A->cap>1){
        int newcap=A->cap/2;
        int *tmp = realloc(A->arr, newcap * sizeof(int));
        if (!tmp) {
            printf("pop:Realloc failed");
            return v;
        }
        A->arr=tmp;
        A->cap=newcap;
    }
    return v;
}

int get(Array A,int index)
{ 
    if (!A){
        printf("Array does not exist.\n");
        return 0;
    }
    if (index>=0 && index<A->size){
        printf("%d\n",A->arr[index]);
        return A->arr[index];
    }else{
        printf("get:Element does not exist\n");
        return 0;
    }
}

int size(Array A)
{
    return A->size;
}

int  cap(Array A)
{
    return A->cap;
}

void test(Array A)
{
    for (int i=0;i<100000;i++){
        push(A,i);
    }
    for (int i=100000;i>10;i--){
        int v=pop(A);
    }
    printf("%d",A->cap);
}


int main(void)
{
    int N;
    Array A=create();
    char oper[10];
    scanf("%d",&N);
    while(N--){
        scanf("%s",oper);
        if (strcmp(oper,"push")==0){
            int num;
            scanf("%d",&num);
            push(A,num);
        }else if(strcmp(oper,"pop")==0){
            int num=pop(A);
            printf("%d\n",num);
        }else if(strcmp(oper,"get")==0){
            int index;
            scanf("%d",&index);
            get(A,index);
        }else if(strcmp(oper,"cap")==0){
            int num=cap(A);
            printf("%d\n",num);
        }else if(strcmp(oper,"size")==0){
            int num=size(A);
            printf("%d\n",num);
        }
    }
    //test(A);
    free(A->arr);
    free(A);
    return 0;
}