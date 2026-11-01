#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define maxsize 10

typedef struct StackNode *Stack;
struct StackNode
{
    int *arr;
    int rear;
    int cat;
};

Stack create()
{
    Stack S=(Stack)malloc(sizeof(struct StackNode));
    if(!S){
        printf("create:malloc failed\n");
        return NULL;
    }
    S->arr=(int *)malloc(maxsize*sizeof(int));
    if(!S->arr){
        printf("create:malloc failed\n");
        return NULL;
    }
    S->cat=maxsize;
    S->rear=0;
    return S;
}

void push(Stack S,int num)
{
    if(!S){
        printf("push:Stack does not exist\n");
        return;
    }
    if(S->rear==S->cat){
        int *tmp=S->arr;
        S->arr=realloc(S->arr,(S->cat+maxsize)*sizeof(int));
        if(!S->arr){
            printf("push:realloc failed\n");
            S->arr=tmp;
            return;
        }
        S->cat+=maxsize;
    }
    S->arr[S->rear]=num;
    S->rear++;
    return;
}

int pop(Stack S)
{
    if(!S){
        printf("pop:Stack does not exist\n");
        return 0;
    }
    if(S->rear==0){
        return 0;
    }
    int t=S->arr[S->rear-1];
    S->rear--;
    return t;
}

int check(Stack S,int num)
{
    int t=pop(S);
    if(t==num){
        return 1;
    }else{
        return 0;
    }
}

void Free(Stack S)
{
    free(S->arr);
    free(S);
    return;
}

int main()
{
    char c='\0';
    Stack S=create();
    int valid=1;
    while(scanf(" %c",&c)==1){
        if(c=='('){
            push(S,1);
        }else if(c=='['){
            push(S,2);
        }else if(c=='{'){
            push(S,3);
        }else if(c==')'){
            if(!check(S,1)){
                valid=0;
                break;
            }
        }else if(c==']'){
            if(!check(S,2)){
                valid=0;
                break;
            }
        }else if(c=='}'){
            if(!check(S,3)){
                valid=0;
                break;
            }
        }
    }
    if(valid && S->rear==0){
        printf("YES\n");
    }else{
        printf("NO\n");
    }
    Free(S);
    return 0;
}