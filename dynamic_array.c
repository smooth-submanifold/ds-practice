#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Len sizeof(int)

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
        printf("Allocating failed.");
        return NULL;
    }
    A->arr=(int*)malloc(Len);
    if(!A->arr){
        printf("Allocating failed.");
        return NULL;
    }
    A->size=0;
    A->cap=1;
    return A;
}

void push(Array A)
{
    int num;
    if (!A){
        printf("Array does not exist.");
        return ;
    }
    scanf("%d",&num);
    if (A->size==A->cap){
        A->cap*=2;
        A->arr=(int*)realloc(A->arr,A->cap*Len);
        if(!A->arr){
            printf("Allocating failed.");
            return ;
        }
    }
    A->arr[A->size]=num;
    A->size++;
}

int pop(Array A)
{
    if (!A){
        printf("Array does not exist.");
        return 0;
    }
    if (4*A->size<=A->cap){
        A->cap/=2;
        A->arr=(int*)realloc(A->arr,A->cap*Len);
    }
    A->size--;
    return A->arr[A->size+1];
}

int get(Array A)
{
    int index;
    
    if (!A){
        printf("Array does not exist.");
        return 0;
    }
    scanf("%d",&index);
    if (index<A->size){
        printf("%d",A->arr[index]);
        return A->arr[index];
    }else{
        printf("Element does not exist");
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
            push(A);
        }else if(strcmp(oper,"pop")==0){
            pop(A);
        }else if(strcmp(oper,"get")==0){
            get(A);
        }else if(strcmp(oper,"cap")==0){
            cap(A);
        }
    }
    free(A->arr);
    free(A);
    return 0;
}