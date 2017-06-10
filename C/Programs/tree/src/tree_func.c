#include "tree.h"

void create_tree (Node **root, int *list, int size_of_list)
{
    int i;

    for (i = 0; i < size_of_list; i++) {
        Node *new_node = (Node*) malloc (sizeof(Node));
        if (!new_node) {
            printf("malloc failed\n");
            return;
        }
        new_node->key = list[i];
        new_node->left = NULL;
        new_node->right = NULL;

        if (*root == NULL) {
            *root = new_node;
           // printf("%d inserted at root\n",(*root)->key);
        } else {
            Node *temp = *root, *parent;
            while (temp != NULL) {
                parent = temp;
                if (list[i] <= temp->key) {
                    if (temp->left == NULL) {
                        temp->left = new_node;
                        //printf("%d inserted under %d\n",new_node->key, parent->key);
                        break;
                    }
                    temp = temp->left;
                } else {
                    if (temp->right == NULL) {
                        temp->right = new_node;
                       // printf("%d inserted under %d\n",new_node->key, parent->key);
                        break;
                    }
                    temp = temp->right;
                }
            }
        }
    }
    printf("Tree created\n");
}

void show_tree_inorder (Node **root)
{
    if (*root == NULL) {
        return;
    }
    show_tree_inorder(&(*root)->left);
    printf("%d,  ",(*root)->key);
    show_tree_inorder(&(*root)->right);
}


void show_tree_preorder (Node **root)
{
    if (*root == NULL) {
        return;
    }

    printf("%d,  ",(*root)->key);
    show_tree_preorder(&(*root)->left);
    show_tree_preorder(&(*root)->right);
}

void show_tree_postorder (Node **root)
{
        if (*root == NULL) {
            return;
        }   

        show_tree_postorder(&(*root)->left);
        show_tree_postorder(&(*root)->right);
        printf("%d,  ",(*root)->key);
}  

void level_order_traversal (Node **root)
{
    if (*root == NULL) {
        return;
    }
    
    Queue q;
    Node *temp;
    create_queue(&q);
    enqueue(&q, *root);
    while (!is_queue_empty(&q)) {
        temp = dequeue(&q);
        printf("%d, ",temp->key);
        if (temp->left) {
            enqueue(&q, temp->left);
        }
        if(temp->right) {
            enqueue(&q, temp->right);
        }
    }
    delete_queue(&q);
}

void level_order_traversal_reverse (Node **root)
{
    if (*root == NULL) {
        return;
    }

    Stack s;
    Queue q;
    Node *temp;
    create_stack(&s);
    create_queue(&q);
    enqueue(&q, *root);

    while (!is_queue_empty(&q)) {
        temp = dequeue(&q);
        push(&s, temp);
        if(temp->right) {
            enqueue(&q, temp->right);
        }
        if (temp->left) {
            enqueue(&q, temp->left);
        }
    }
    while (!is_stack_empty(&s)) {
        temp = pop(&s);
        printf("%d, ", temp->key);
    }
    delete_stack(&s);
    delete_queue(&q);
}



Node* find_min (Node **root) 
{
    Node *temp = *root;
    while (temp->left != NULL) {
        temp = temp->left;
    } 
    return temp;
}

Node* find_max (Node **root)
{
    Node *temp = *root;
    while (temp->right != NULL) {
        temp = temp->right;
    }
    return temp;
}

Node* search_node (Node **root, int item)
{
    if ((*root == NULL) || ((*root)->key == item)) {
        return *root;
    }

    if (item < (*root)->key) {
        return search_node(&(*root)->left, item);
    }
    
    return search_node(&(*root)->right, item);
}




Node* delete_node (Node *root, int item)
{
    if (root == NULL) {
        return root;
    }

    if (item < root->key) {
        root->left = delete_node(root->left, item);
    } else if (item > root->key) {
        root->right = delete_node(root->right, item);
    } else if (item == root->key) {
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        } else {
            Node *temp = find_min(&root->right);
            root->key = temp->key;
            root->right = delete_node(root->right, temp->key);
        }
    }
    return root;
}


void tree_mirror_image (Node **root) 
{
   if (*root) {
        tree_mirror_image(&(*root)->left);
        tree_mirror_image(&(*root)->right);

        Node *temp = (*root)->left;
        (*root)->left = (*root)->right;
        (*root)->right = temp;
    }
/*
    if ((!(*root)->left && !(*root)->right) || !(*root)) {
        return;
    } else {
        Node *temp;
        if (!(*root)->left) {
            (*root)->left = (*root)->right;
            (*root)->right = NULL;
        } else if (!(*root)->right) {
            (*root)->right = (*root)->left;
            (*root)->left = NULL;
        } else {
            temp = (*root)->left;
            (*root)->left = (*root)->right;
            (*root)->right = temp;
        }
    }
    if ((*root)->left) {
    tree_mirror_image(&(*root)->left);
    }
    if((*root)->right) {
    tree_mirror_image(&(*root)->right);
    }
    */

}

int find_item_index (int *array, int start, int end, int item)
{
    int index;
    for (index = start; index <= end; index++) {
        if (array[index] == item) {
            return index;
        }
    }
    return -1;
}


Node*  build_tree (int *inorder, int *preorder, int in_start, int in_end)
{
    if (in_start > in_end) {
        return NULL;
    }

    static int preindex = 0;
    int in_index;

    Node *root = (Node*) malloc (sizeof(Node));
    if (!root) {
        printf("Malloc failed in build_tree func\n");
        return NULL;
    }
 
    root->key = preorder[preindex];
    preindex++;
    if (in_start == in_end) {
        return root;
    }
    in_index = find_item_index(inorder, in_start, in_end, root->key);
    if (in_index != -1) {
        root->left = build_tree(inorder, preorder, in_start, in_index -1);
        root->right = build_tree(inorder, preorder, in_index+1, in_end);
        return root;
    } else {
        printf("Inorder/Preorder tree traversal given in input are not correct\n");
        return NULL;
    }
}
/*   
void zigzag_traversal (Node **root, int level) 
{
    Queue q;
    Node *temp;
    create_queue(&q);
    enqueue(&q, *root);

    while (!is_queue_empty(&q)) {
        temp = dequeue(&q);
        printf("%d(%d), ",temp->key, level);
        if (level % 2 == 0) {
            enqueue(&q, temp->right);
            enqueue(&q, temp->left);
        } else {
            enqueue(&q, temp->left);
            enqueue(&q, temp->right);
        }
    }
    delete_queue(&q);
}


*/




























