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

int pop(Stack S,int *out)
{
    if(!S){
        return 1;       //栈不存在
    }
    if(S->rear==0){
        return 2;       //栈空
    }
    int t=S->arr[S->rear-1];
    S->rear--;
    *out=t;
    return 0;
}

int calculate(Stack S,int oper)
{
    int a,b,pop_a,pop_b,res;
    pop_a=pop(S,&a);
    if(pop_a==1){
        return 1;
    }else if(pop_a==2){
        return 2;
    }
    pop_b=pop(S,&b);
    if(pop_b==1){
        return 1;
    }else if(pop_b==2){
        return 2;
    }
    if(oper==1){
        res=a+b;
        push(S,res);
        return 0;
    }else if(oper==2){
        res=b-a;
        push(S,res);
        return 0;
    }else if(oper==3){
        res=a*b;
        push(S,res);
        return 0;
    }else if(oper==4){
        if(a==0){
            return 3;       //3:除以0
        }
        res=b/a;
        push(S,res);
        return 0;
    }
    return 0;
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
    int valid=1,cal=0;
    while(scanf(" %c",&c)==1){
        if(c>='0' && c<='9'){
            push(S,(int)(c-'0'));
        }else if(c=='+'){
            if((cal=calculate(S,1))!=0) break;
        }else if(c=='-'){
            if((cal=calculate(S,2))!=0) break;
        }else if(c=='*'){
            if((cal=calculate(S,3))!=0) break;
        }else if(c=='/'){
            if((cal=calculate(S,4))!=0) break;
        }else{
            valid=0;
            break;
        }
    }
    if(!valid){
        printf("Invalid input\n");
    }else if(cal==1){
        printf("Stack does not exist\n");
    }else if(cal==2){
        printf("Stack is empty\n");
    }else if(cal==3){
        printf("0 cannot be a divisor\n");
    }else if(S->rear!=1){
        printf("Invalid formula\n");
    }else if(cal==0){
        printf("%d",S->arr[0]);
    }
    Free(S);
    return 0;
}