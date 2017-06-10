#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
}Node;

//Node *head1 = NULL;

/*
void insert_element_at_start(Node **head, int data)
{
    Node *new = (Node*) malloc (sizeof(Node));
    if(!new) { 
        printf("Malloc error\n");
        return;
    }
    new->data = data;
    if(*head==NULL) {
        new->next = NULL;
    } else {
        new->next = *head;
    }
    *head = new;
}

void print_list(Node **head) {
    Node *p = *head;
    printf("List is :");
    while (p != NULL) {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}
*/

Node* insert_element_at_start1(Node *head1, int data)
{
    Node *new = (Node*) malloc (sizeof(Node));
    if(!new) { 
        printf("Malloc error\n");
        return head1;
    }
    new->data = data;
    if(head1==NULL) {
        new->next = NULL;
    } else {
        new->next = head1;
    }
    head1 = new;
    return head1;
}

void print_list1(Node *head1) {
    Node *p = head1;
    printf("List is :");
    while (p != NULL) {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}

void print_list_recursive(Node *head1) {
    if(head1 != NULL) {
        printf("%d ",head1->data);
        print_list_recursive(head1->next);
    }
}

void print_list_reverse(Node *head1) {
    if(head1 != NULL) {
        print_list_reverse(head1->next);
	 printf("%d ",head1->data);
    }
}

Node* reverse_list(Node *head1) {
    Node *p, *q = NULL;
    while(head1) {
        p = head1;
        head1 = head1->next;
        p->next = q;
        q = p;
    }
    return p;
}
/*
Node* reverse_list_recorsive(Node *head1) {
    Node *p, *q=NULL;
    if(head1 == NULL) {
        return head1;
    } else {
        p = head1;
        head1 = head1->next;
        p->next = q;
        q = ;

}
*/

int main ()
{
/*
    Node *head = NULL;
    insert_element_at_start(&head, 10);
    print_list(&head);
*/
    Node *head1 = NULL;
    head1 = insert_element_at_start1(head1, 10);
    head1 = insert_element_at_start1(head1, 20);
    head1 = insert_element_at_start1(head1, 30);
    print_list1(head1);
    head1 = reverse_list(head1);
    print_list1(head1);
    printf("List in recursvive call: ");
    print_list_recursive(head1);
    printf("\nList is reverse: ");
    print_list_reverse(head1);
    printf("\n");
   
    return 0;
}

/*
hi my name is nitin jain;
hi my name is rupali jain;
hi my name is rahul;
hi my name is sachin;
*/


