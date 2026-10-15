#include <stdio.h>
#include <stdlib.h>

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    int rthread;
};

// Create a new node
struct TreeNode* createNode(int el)
{
    struct TreeNode *newnode;

    newnode = (struct TreeNode*)malloc(sizeof(struct TreeNode));

    if(newnode == NULL)
    {
        printf("Memory allocation failed...\n");
        exit(1);
    }

    newnode->val = el;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->rthread = 0;

    return newnode;
}

// Insert a node
void addNode(struct TreeNode **root, int el)
{
    struct TreeNode *newnode = createNode(el);

    if(*root == NULL)
    {
        *root = newnode;
        printf("Node inserted successfully.\n");
        return;
    }

    struct TreeNode *current = *root;
    struct TreeNode *parent = NULL;

    while(current != NULL)
    {
        if(el == current->val)
        {
            printf("Duplicate value not allowed...\n");
            free(newnode);
            return;
        }

        parent = current;
        if(el < current->val)
        {
            current = current->left;
        }
        else
        {
            if(current->rthread == 0)
            {
                current = current->right;
            }
            else
            {
                current = NULL;
            }
        }
    }

    // Insert as left child
    if(el < parent->val)
    {
        newnode->left = NULL;
        newnode->right = parent;
        newnode->rthread = 1;

        parent->left = newnode;
    }

    // Insert as right child
    else
    {
        newnode->left = NULL;
        newnode->right = parent->right;
        newnode->rthread = 1;

        parent->right = newnode;
        parent->rthread = 0;
    }

    printf("Node inserted successfully.\n");
}

// Inorder traversal-left root right
void inorder(struct TreeNode *root)
{
    if(root == NULL)
    {
        printf("Tree is empty...\n");
        return;
    }

    struct TreeNode *current = root;

    // Go to the leftmost node
    while(current->left != NULL)
    {
        current = current->left;
    }

    while(current != NULL)
    {
        printf("%d ", current->val);

        // If right pointer is a thread
        if(current->rthread == 1)
        {
            current = current->right;
        }

        // If right pointer is a real child
        else
        {
            current = current->right;

            while(current != NULL && current->left != NULL)
            {
                current = current->left;
            }
        }
    }
    printf("\n");
}

// Preorder traversal
void preorder(struct TreeNode *root)
{
    if(root == NULL)
    {
        printf("Tree is empty...\n");
        return;
    }

    struct TreeNode *current = root;

    while(current != NULL)
    {
        printf("%d ", current->val);

        // If a left child exists, visit it first
        if(current->left != NULL)
        {
            current = current->left;
        }
        else
        {
            // Follow threads until a real right child is found
            while(current != NULL && current->rthread == 1)
            {
                current = current->right;
            }

            // Move to the real right child
            if(current != NULL)
            {
                current = current->right;
            }
        }
    }
    printf("\n");
}

// Search a value
void searchNode(struct TreeNode *root, int target)
{
    struct TreeNode *current = root;

    while(current != NULL)
    {
        if(current->val == target)
        {
            printf("Node found.\n");
            return;
        }

        if(target < current->val)
        {
            current = current->left;
        }
        else
        {
            if(current->rthread == 0)
            {
                current = current->right;
            }
            else
            {
                break;
            }
        }
    }

    printf("Node not found.\n");
}

// Delete a node
void deleteNode(struct TreeNode **root, int target)
{
    if(*root == NULL)
    {
        printf("Tree is empty...\n");
        return;
    }

    struct TreeNode *current = *root;
    struct TreeNode *parent = NULL;

    // Search for the node
    while(current != NULL && current->val != target)
    {
        parent = current;

        if(target < current->val)
        {
            current = current->left;
        }
        else
        {
            if(current->rthread == 0)
            {
                current = current->right;
            }
            else
            {
                current = NULL;
            }
        }
    }

    if(current == NULL)
    {
        printf("Node not found...\n");
        return;
    }

    // Case 1: Node has no children
    if(current->left == NULL && current->rthread == 1)
    {
        if(parent == NULL)
        {
            *root = NULL;
        }
        else if(parent->left == current)
        {
            parent->left = NULL;
        }
        else
        {
            // Preserve the deleted node's successor thread
            parent->right = current->right;
            parent->rthread = 1;
        }

        free(current);
        printf("Node deleted successfully.\n");
    }

    // Case 2: Node has only a left child
    else if(current->rthread == 1)
    {
        struct TreeNode *predecessor = current->left;

        // Find the rightmost node in the left subtree
        while(predecessor->rthread == 0)
        {
            predecessor = predecessor->right;
        }

        // Redirect predecessor's thread to current's successor
        predecessor->right = current->right;

        if(parent == NULL)
        {
            *root = current->left;
        }
        else if(parent->left == current)
        {
            parent->left = current->left;
        }
        else
        {
            parent->right = current->left;
            parent->rthread = 0;
        }

        free(current);
        printf("Node deleted successfully.\n");
    }

    // Case 3: Node has only a right child
    else if(current->left == NULL)
    {
        if(parent == NULL)
        {
            *root = current->right;
        }
        else if(parent->left == current)
        {
            parent->left = current->right;
        }
        else
        {
            parent->right = current->right;
            parent->rthread = 0;
        }

        free(current);
        printf("Node deleted successfully.\n");
    }

    // Case 4: Node has two children
    else
    {
        // Find the inorder successor
        struct TreeNode *successor = current->right;
        struct TreeNode *successorParent = current;

        while(successor->left != NULL)
        {
            successorParent = successor;
            successor = successor->left;
        }

        // Copy successor's value
        current->val = successor->val;

        // Remove the successor while preserving its right link
        if(successorParent == current)
        {
            current->right = successor->right;
            current->rthread = successor->rthread;
        }
        else
        {
            if(successor->rthread == 0)
            {
                successorParent->left = successor->right;
            }
            else
            {
                successorParent->left = NULL;
            }
        }

        free(successor);
        printf("Node deleted successfully.\n");
    }
}

// Update a node's value
void updateNode(struct TreeNode **root, int oldval, int newval)
{
    if(*root == NULL)
    {
        printf("Tree is empty...\n");
        return;
    }

    // Check whether old value exists
    struct TreeNode *current = *root;

    while(current != NULL && current->val != oldval)
    {
        if(oldval < current->val)
        {
            current = current->left;
        }
        else
        {
            if(current->rthread == 0)
            {
                current = current->right;
            }
            else
            {
                current = NULL;
            }
        }
    }

    if(current == NULL)
    {
        printf("Node with value %d not found.\n", oldval);
        return;
    }

    // No change is needed if both values are the same
    if(oldval == newval)
    {
        printf("Old and new values are the same. No update needed.\n");
        return;
    }

    // Check whether the new value already exists
    current = *root;

    while(current != NULL)
    {
        if(current->val == newval)
        {
            printf("New value already exists! Update not allowed.\n");
            return;
        }

        if(newval < current->val)
        {
            current = current->left;
        }
        else
        {
            if(current->rthread == 0)
            {
                current = current->right;
            }
            else
            {
                current = NULL;
            }
        }
    }

    // Delete old value and insert new value
    deleteNode(root, oldval);
    addNode(root, newval);

    printf("Node updated successfully.\n");
}

// Main function
int main()
{
    struct TreeNode *root = NULL;

    int choice;
    int val;
    int oldval;
    int newval;

    while(1)
    {
        printf("\n");
        printf("----- RIGHT-THREADED BST -----\n");
        printf("1. Insert\n");
        printf("2. Inorder Traversal\n");
        printf("3. Preorder Traversal\n");
        printf("4. Search\n");
        printf("5. Delete\n");
        printf("6. Update\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);

                addNode(&root, val);
                break;

            case 2:
                printf("Inorder Traversal: ");
                inorder(root);
                break;

            case 3:
                printf("Preorder Traversal: ");
                preorder(root);
                break;

            case 4:
                printf("Enter value to search: ");
                scanf("%d", &val);

                searchNode(root, val);
                break;

            case 5:
                printf("Enter value to delete: ");
                scanf("%d", &val);

                deleteNode(&root, val);
                break;

            case 6:
                printf("Enter old value: ");
                scanf("%d", &oldval);

                printf("Enter new value: ");
                scanf("%d", &newval);

                updateNode(&root, oldval, newval);
                break;

            case 7:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice...\n");
        }
    }

    return 0;
}
