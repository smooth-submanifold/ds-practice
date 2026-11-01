#include <stdio.h>
#include <stdlib.h>

typedef struct Node* Link;
struct Node
{
    int num;
    Link next;
};

Link create()
{
    Link L=(Link)malloc(sizeof(struct Node));
    if(!L){
        printf("create:malloc failed");
        return NULL;
    }
    L->num=0;
    L->next=NULL;
    return L;
}

void Insert(Link *pr,int num)
{
    if(!(*pr)){
        printf("Insert:link does not exist");
        return ;
    }
    (*pr)->next=create();
    (*pr)->next->num=num;
    (*pr)=(*pr)->next;
    return ;
}

void PrintLink(Link head)
{
    if(!(head)){
        printf("PrintLink:link does not exist");
        return ;
    }
    head=head->next;
    while(head){
        printf("%d",head->num);
        head=head->next;
    }
    return ;
}

void FreeLink(Link head)
{
    if(!(head)){
        printf("FreeLink:link does not exist");
        return ;
    }
    Link tmp=head->next;
    while(tmp){
        free(head);
        head=tmp;
        tmp=tmp->next;
    }
    free(head);
}

int main()
{
    int n=0,k=0,num;
    scanf("%d %d",&n,&k);
    if(n<=0 || k<=0 || k>n){
        printf("error");
        return 1;
    }
    Link head=create();
    Link rear=head;
    for(int i=1;i<=n-k;i++){
        scanf("%d",&num);
        Insert(&rear,num);
    }
    for(int i=n-k+1;i<=n;i++){
        scanf("%d",&num);
        Insert(&rear,num);
    }
    PrintLink(head);
    FreeLink(head);
    return 0;
}