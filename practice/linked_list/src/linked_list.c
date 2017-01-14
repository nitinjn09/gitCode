#include "../include/linked_list.h"

int main ()
{
    Node *head = NULL, *head_2 = NULL, *head_3;
    dNode *dhead = NULL;
    int list[10] = {1,3,5,7,8,11,13,15,17,19};
    int list_2[10] = {2,4,6,8,10,12,14,16,18,20};
    int size_of_list = 10;
    int choice;
/*
create_list(&head, list, 10);
Node *temp = head;
free(head);
show_list(&temp);
*/
    while (1) {
        printf("Enter your choice\n");
        printf(" 1. create list-1\n 2. create list-2\n 3. create d-list\n 4. swap nodes\n "
                "5. swap nodes without data swap\n 6. reverse list\n 7. list intersection\n "
                "8. merge two sorted list\n 9. detect loop in list\n 0. EXIT\n");
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                create_list(&head, list, 10);
                show_list(&head);
                break;
            case 2:
                create_list(&head_2, list_2, 10);
                show_list(&head_2);
                break;
            case 3:
                create_dlist(&dhead, list, 10);
                show_dlist(&dhead);
                break;
            case 4:
                swap_nodes(&head, 1, 10);
                show_list(&head);
                break;
            case 5:
                swap_nodes_without_data_swap(&head, 1, 1);
                show_list(&head);
                break;
            case 6:
                reverse_list(&head);
                show_list(&head);
                break;
            case 7:
                // Node *head_3 = list_intersection(&head, &head_2);
                    head_3 = list_intersection_1(head, head_2);
                    show_list(&head_3);
                break;
            case 8:
                head_3 = merge_two_sorted_list(&head, &head_2);
                show_list(&head_3);
                break;
            case 9:
                head->next->next->next->next = head;
                int (*func_ptr)(Node**) = &detect_loop_in_list;
                (*func_ptr)(&head);
                //detect_loop_in_list(&head);
                break;
            case 0: 
                return 0;
            default:
                printf("Invalid choice. Enter again\n");
                break;
        }
    }

    return 0;
}
/*
void create_list (Node **head, int *list, int size_of_list)
{
    int index;
    for (index = 0; index < size_of_list; index++) {
        insert_item_in_list_at_last_pos(&(*head), list[index]);
    }
    printf("list created successfully\n");
}

void create_dlist (dNode **dhead, int *list, int size_of_list)
{
    int index;
    for (index = 0; index < size_of_list; index++) {
        dNode *new_node = (dNode*) malloc (sizeof(dNode));
        new_node->data = list[index];
        if (*dhead == NULL) {
            *dhead = new_node;
            new_node->prev = NULL;
        } else {
            dNode *temp = *dhead;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_node;
            new_node->prev = temp;
        }
        new_node->next = NULL;
    }
    printf("dlist created\n");

}

        
void insert_item_in_list_at_last_pos (Node **head, int data)
{
    Node *new_node = (Node*) malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("malloc failed\n");
        return;
    }

    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}



void swap_nodes (Node **head, int x, int y)
{
    if (*head == NULL) {
        printf("list empty\n");
        return;
    }

    if (x == y) {
        printf("Both items are same\n");
        return;
    }

    Node *node_x = *head, *node_y = *head;
    int temp_data;

    while (node_x->data != x) {
        node_x = node_x->next;
        if (node_x == NULL) {
            printf("item %d not found\n", x);
            return;
        }
    }
    while (node_y->data != y) {
        node_y = node_y->next;
        if (node_y == NULL) {
            printf("item %d not found", y);
            return;
        }
    }

    temp_data = node_x->data;
    node_x->data = node_y->data;
    node_y->data = temp_data;

    return;
}

void swap_nodes_without_data_swap (Node **head, int x, int y)
{
    if (*head == NULL) {
        printf("Empty list\n");
        return;
    }

    if (x == y) {
        printf("Both items are same\n");
        return;
    }

    Node *prv_x = NULL, *curr_x = *head;

    while (curr_x && curr_x->data != x) {
        prv_x = curr_x;
        curr_x = curr_x->next;
        if(curr_x == NULL) {
            printf("item %d not found", x);
            return;
        }
    }

    Node *prv_y = NULL, *curr_y = *head;
    
    while (curr_y && curr_y->data != y) {
          prv_y = curr_y;
          curr_y = curr_y->next;
          if(curr_y == NULL) {
             printf("item %d not found", y);
             return;
          }
    }
 
    if (prv_x != NULL) {
        prv_x->next = curr_y;
    } else {
        *head = curr_y;
    }

    if (prv_y != NULL) {
        prv_y->next = curr_x;
    } else {
        *head = curr_x;
    }

    Node *temp_node;
    temp_node = curr_y->next;
    curr_y->next = curr_x->next;
    curr_x->next = temp_node;

    return;
}

void reverse_list(Node **head)
{
    if ((*head == NULL) || ((*head)->next == NULL)) {
        return;
    }

    Node *prv_node = NULL, *curr_node = *head, *next_node;
    while (curr_node != NULL) {
        next_node = curr_node->next;
        curr_node->next = prv_node;
        prv_node = curr_node;
        curr_node = next_node;
    }
    *head = prv_node;

    return;
}


Node* merge_two_sorted_list(Node **head, Node **head_2) 
{
    if (*head == NULL) {
        return *head_2;
    } else if (*head_2 == NULL) {
        return *head;
    }

    Node *temp_node = *head, *temp_node_2 = *head_2, *head_sorted = NULL; 

    while ((temp_node != NULL) && (temp_node_2 != NULL)) {
        if (temp_node->data <= temp_node_2->data) {
            insert_item_in_list_at_last_pos(&head_sorted, temp_node->data);
            temp_node = temp_node->next;
        } else if (temp_node->data > temp_node_2->data) {
            insert_item_in_list_at_last_pos(&head_sorted, temp_node_2->data);
            temp_node_2 = temp_node_2->next;
        }
    }

    if ((temp_node == NULL) && (temp_node_2 != NULL)) {
        while (temp_node_2 != NULL) {
            insert_item_in_list_at_last_pos(&head_sorted, temp_node_2->data);
            temp_node_2 = temp_node_2->next;
        }
    } else if ((temp_node != NULL) && (temp_node_2 == NULL)) {
        while (temp_node != NULL) {
            insert_item_in_list_at_last_pos(&head_sorted, temp_node->data);
            temp_node = temp_node->next;
        }
    }

    return head_sorted;
}

Node* list_intersection (Node **head, Node **head_2)
{
    if ((*head == NULL) || (*head_2 == NULL)) {
        return NULL;
    }

    Node *temp = *head, *temp_2 = *head_2, *head_3 = NULL;
    while (temp != NULL) {
        temp_2 = *head_2;
        while (temp_2 != NULL) {
            if (temp->data == temp_2->data) {
                insert_item_in_list_at_last_pos(&head_3, temp->data);
                break;
            }
            temp_2 = temp_2->next;
        }
        temp = temp->next;
    }
    return head_3;
}



Node* list_intersection_1 (Node *head, Node *head_2)
{
        if ((head == NULL) || (head_2 == NULL)) {
            return NULL;
        }

            Node *temp = head, *temp_2 = head_2, *head_3 = NULL;
                while (temp != NULL) {
                            temp_2 = head_2;
                                    while (temp_2 != NULL) {
                                                    if (temp->data == temp_2->data) {
                                                                        insert_item_in_list_at_last_pos(&head_3, temp->data);
                                                                                        break;
                                                                                                    }
                                                                temp_2 = temp_2->next;
                                                                        }
                                            temp = temp->next;
                                                }
                    return head_3;
}

int detect_loop_in_list(Node **head)
{
    Node *slow = *head, *fast = *head;
    while (slow && fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            printf("Loop found\n");
            return 1;
        }
    }
    return 0;
}


void show_list (Node **head)
{
    Node *temp = *head;
    printf("List is: \n");
    while (temp != NULL) {
        printf("%d  ",temp->data);
        temp = temp->next;
    }
    printf("\n\n");
}

void show_dlist (dNode **dhead)
{
    dNode *temp = *dhead;
    printf(" fwd dList is:\n");
    while(temp->next != NULL) {
        printf ("%d  ",temp->data);
        temp = temp->next;
    }
    printf("%d  ",temp->data);

    printf("\n backwd dList is : \n");
    while (temp != NULL) {
        printf("%d  ",temp->data);
        temp = temp->prev;
    }
    printf("\n\n");
}

int list_size(Node **head)
{
    Node *temp_node = *head;
    int count = 0;

    while (temp_node != NULL) {
        temp_node = temp_node->next;
        count++;
    }
    return count;
}

*/
