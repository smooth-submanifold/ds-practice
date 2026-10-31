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
        printf("Allocating failed.\n");
        return NULL;
    }
    A->arr=(int*)malloc(sizeof(int));
    if(!A->arr){
        printf("Allocating failed.\n");
        free(A)
        return NULL;
    }
    A->size=0;
    A->cap=1;
    return A;
}

void push(Array A,int num)
{
    int num;
    if (!A){
        printf("Array does not exist.\n");
        return ;
    }
    if (A->size==A->cap){
        A->cap*=2;
        int *tmp = realloc(A->arr, cap * sizeof(int));
        if (!tmp) A->arr = tmp;
        else{
            printf("Allocating failed.\n");
            return ;
        }
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
        printf("Element does not exist.\n");
    }
    int v=A->arr[A->size-1];
    A->size--;
    if (4*A->size<=A->cap && cap>1){
        A->cap/=2;
        int *tmp = realloc(A->arr, cap * sizeof(int));
        if (!tmp) A->arr = tmp;
    }
    printf("%d",A->arr[A->size]);
    return v;
}

int get(Array A,int index)
{ 
    if (!A){
        printf("Array does not exist.\n");
        return 0;
    }
    if (index>0 && index<A->size){
        printf("%d",A->arr[index]);
        return A->arr[index];
    }else{
        printf("Element does not exist\n");
        return 0;
    }
}

void size(Array A)
{
    printf("%d",A->size);
}

void cap(Array A)
{
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
            scanf("%d",&num)
            push(A,num);
        }else if(strcmp(oper,"pop")==0){
            int num=pop(A);
            printf("%d",num);
        }else if(strcmp(oper,"get")==0){
            int index;
            scanf("%d",&index)
            get(A,index);
        }else if(strcmp(oper,"cap")==0){
            int num=cap(A);
            printF("%d",num);
        }else if(strcmp(oper,"size")==0){
            int num=size(A);
            printf("%d",num);
    }
    free(A->arr);
    free(A);
    return 0;
}