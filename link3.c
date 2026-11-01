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
        printf("create:malloc failed\n");
        return NULL;
    }
    L->num=0;
    L->next=NULL;
    return L;
}

void Insert(Link *pr,int num)
{
    if(!(*pr)){
        printf("Insert:link does not exist\n");
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
        printf("PrintLink:link does not exist\n");
        return ;
    }
    head=head->next;
    while(head){
        printf("%d ",head->num);
        head=head->next;
    }
    printf("\n");
    return ;
}

void FreeLink(Link head)
{
    if(!(head)){
        printf("FreeLink:link does not exist\n");
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

Link ScanLink(int len)
{
    Link h=create();
    Link r=h;
    int num;
    while(len--){
        scanf("%d",&num);
        Insert(&r,num);
    }
    return h;
}

Link Merge(Link h1,Link h2)
{
    Link h=h1;
    Link r=h2->next;
    h1=h1->next;
    h2=r;
    r=h;
    while(h1 && h2){
        if(h1->num<h2->num){
            r->next=h1;
            r=h1;
            h1=h1->next;
            r->next=NULL;
        }else{
            r->next=h2;
            r=h2;
            h2=h2->next;
            r->next=NULL;
        }
    }
    if(!h1){
        r->next=h2;
    }else{
        r->next=h1;
    }
    return h;
}

int main()
{
    int n1=0,n2=0;
    int res=scanf("%d %d",&n1,&n2);
    if(res<2 || n1<0 || n2<0){
        printf("Invalid input\n");
        return 1;
    }
    Link h1=ScanLink(n1);
    Link h2=ScanLink(n2);
    Link h=Merge(h1,h2);
    free(h2);
    PrintLink(h);
    FreeLink(h);
    return 0;
}