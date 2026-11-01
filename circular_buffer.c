#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct CircleNode* Circle;
struct CircleNode//环形队列
{
    int *arr;
    int front,rear;
    int cap;
    int count;
};

Circle createC(int n)//创建环形队列
{
    Circle C=(Circle)malloc(sizeof(struct CircleNode));
    if(!C){
        printf("creataC:malloc failed\n");
        return NULL;
    }
    C->arr=(int *)malloc(n*sizeof(int));
    C->front=0;
    C->rear=0;
    C->cap=n;
    C->count=0;
    return C;
}

void enqueue(Circle C,int num)//入队
{
    if(!C){
        printf("enqueue:Circle does not exist\n");
        return;
    }
    if(C->count==C->cap){
        printf("FULL\n");
        return;
    }
    C->arr[C->rear%C->cap]=num;
    C->rear++;
    C->rear%=C->cap;
    C->count++;
    return;
}


void dequeue(Circle C)
{
    if(!C){
        printf("dequeue:circle does not exist\n");
        return;
    }
    if(C->count==0){
        printf("NA\n");
        return;
    }
    printf("%d\n",C->arr[C->front]);
    C->front++;
    C->front%=C->cap;
    C->count--;
    return;
}

void size(Circle C)
{
    if(!C){
        printf("size:circle does not exist\n");
        return;
    }
    printf("%d\n",C->count);
    return;
}

void empty(Circle C)
{
    if(!C){
        printf("empty:circle does not exist\n");
        return;
    }
    if(C->count==0){
        printf("YES\n");
    }else{
        printf("NO\n");
    }
    return;
}

void full(Circle C)
{
    if(!C){
        printf("full:circle does not exist\n");
        return;
    }
    if(C->count==C->cap){
        printf("YES\n");
    }else{
       printf("NO\n");
    }
    return;
}

void Free(Circle C)
{
    if(!C){
        printf("Free:Circle does not exist\n");
        return;
    }
    free(C->arr);
    free(C);
    return;
}

int main()
{
    int c=0,m=0;
    int res=scanf("%d %d",&c,&m);
    if(res<2 || c<=1 || m<0){
        printf("Invalid input\n");
        return 1;
    }

    char oper[10];
    Circle C=createC(c);
    while(m--){
        scanf("%s",oper);
        if(strcmp(oper,"enqueue")==0){
            int num=0;
            scanf("%d",&num);
            enqueue(C,num);
        }else if(strcmp(oper,"dequeue")==0){
            dequeue(C);
        }else if(strcmp(oper,"size")==0){
            size(C);
        }else if(strcmp(oper,"empty")==0){
            empty(C);
        }else if(strcmp(oper,"full")==0){
            full(C);
        }
    }
    Free(C);
    return 0;
}