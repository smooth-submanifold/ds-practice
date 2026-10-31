#include<stdio.h>
#include<stdlib.h>

typedef struct Node* Link;
struct Node
{
    int num;
    Link next;
};

Link create()
{
    Link head=(Link)malloc(sizeof(struct Node));
    if (!head){
        printf("create:malloc failed.\n");
        return NULL;
    }
    head->num=0;
    head->next=NULL;
    return head;
}

void Insert(Link *pr,int n)
{
    if (!*pr){
        printf("Insert:link does not exist.\n");
        return;
    }
    (*pr)->next=(Link)malloc(sizeof(struct Node));
    if (!(*pr)->next){
        printf("Insert:malloc failed.\n");
        return;
    }
    (*pr)=(*pr)->next;
    (*pr)->num=n;
    (*pr)->next=NULL;
}

Link Invert1(Link head)
{
    if(!head || ! head->next){
        printf("Invert1:link does not exist.\n");
        return NULL;
    }
    Link behind;
    Link pres=head->next;
    Link front=pres->next;
    pres->next=NULL;
    while(front){
        behind=pres;
        pres=front;
        front=front->next;
        pres->next=behind;
    }
    head->next=pres;
    return head;
}

Link reverse(Link subhead)
{
    if(!subhead->next){
        return subhead;
    }
    Link tmp=reverse(subhead->next);
    while(tmp->next){
        tmp=tmp->next;
    }
    tmp->next=subhead;
    return reverse(subhead);
}

Link Invert2(Link head)
{
    if(!head) return NULL;
    head->next==reverse(head->next);
    return head;
}

void PrintLink(Link L)
{
    L=L->next;
    while(L){
        printf("%d ",L->num);
        L=L->next;
    }
    printf("\n");
}

int main()
{
    int N,n;
    scanf("%d",&N);
    Link head=create();
    Link rear=head;
    while (N--){
        scanf("%d",&n);
        Insert(&rear,n);
    }
    Link res1=Invert1(head);
    PrintLink(res1);
    head=Invert1(head);
    PrintLink(head);
    Link res2=Invert2(head);
    PrintLink(res2);
}