#include "tree.h"

int main()
{
    int list[] = {10, 5, 14, 4, 3, 7, 6, 9, 11, 12, 16, 15, 17};
    int inorder[] = {3,  4,  5,  6,  7,  9,  10,  11,  12,  14,  15,  16,  17};
    int preorder[] = {10,  5,  4,  3,  7,  6,  9,  14,  11,  12,  16,  15,  17};
    Node *root = NULL;
    int choice;
    int size = sizeof(list)/sizeof(list[0]);

    while (1) {
        printf("\n\nEnter your choice:\n 1. Create tree\n 2. Inorder treversal\n 3. PreOrder traversal\n"
                " 4. PostOrder traversal\n 5. level order traversal\n 6. search node\n 7. delete node\n "
                "8. Tree mirror image\n 9. delete tree\n 0. EXIT\n");
        scanf("%d",&choice);

        switch (choice) {
            case 1:
                //create_tree(&root, list, size);
                root = build_tree(inorder, preorder, 0, size-1);
                break;
            case 2: 
                printf("\nInorder tarversal\n");
                show_tree_inorder(&root);
                break;
            case 3:
                printf("Prerder tarversal\n");
                show_tree_preorder(&root);
                break;
            case 4:
                printf("\nPostorder tarversal\n");
                show_tree_postorder(&root);
                break;
            case 5: 
                printf("\nLevel order tarversal\n");
                level_order_traversal(&root);
                printf("\nLevel order tarversal in reverse\n");
                level_order_traversal_reverse(&root);
                break;
            case 6:
                if (search_node(&root, 12)) {
                    printf("item 12 found\n");
                }
                break;
            case 7: 
                root = delete_node(root, 12);
                printf("\nTree after deleting 12\n");
                show_tree_inorder(&root);
                break;
            case 8: 
                tree_mirror_image(&root);
                printf("\nInorder tarversal of mirror tree\n");
                show_tree_inorder(&root);
                break;
            case 9:
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
