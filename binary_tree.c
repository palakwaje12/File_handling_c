#include <stdio.h>
#include <stdlib.h>

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct Queue
{
    struct TreeNode *data[100];
    int front;
    int rear;
};

void initQueue(struct Queue *q)  //queue initialization
{
    q->front = 0;
    q->rear = -1;
}

int isEmpty(struct Queue *q)   //check if queue is empty nd is a user defined function not taken from any lib
{
    return q->front > q->rear;
}

void enqueue(struct Queue *q, struct TreeNode *node)
{
    if(q->rear == 99)
    {
        printf("Queue is full!\n");
        return;
    }
    q->rear++;
    q->data[q->rear] = node;
}

struct TreeNode* dequeue(struct Queue *q)    //to remove node from queue
{
    if(isEmpty(q))
    {
        return NULL;
    }
    return q->data[q->front++];
}

void addNode(struct TreeNode **root, int el)    //to add node
{
    struct TreeNode *newnode;
    newnode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if(newnode == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    newnode->val = el;
    newnode->left = NULL;
    newnode->right = NULL;

    if(*root == NULL)   //to check if root is null
    {
        *root = newnode;
        return;
    }
    struct Queue q;
    initQueue(&q);
    enqueue(&q, *root);
    while(!isEmpty(&q))
    {
        struct TreeNode *node = dequeue(&q);
        /* Check left child */

        if(node->left != NULL)
        {
            enqueue(&q, node->left);
        }
        else
        {
            node->left = newnode;
            return;
        }
        /* Check right child */

        if(node->right != NULL)
        {
            enqueue(&q, node->right);
        }
        else
        {
            node->right = newnode;
            return;
        }
    }
}
//display tree
void readTree(struct TreeNode *root)
{
    if(root == NULL)
    {
        printf("Tree is empty...\n");
        return;
    }
    struct Queue q;

    initQueue(&q);

    enqueue(&q, root);
    while(!isEmpty(&q))
    {
        struct TreeNode *node = dequeue(&q);

        printf("%d ", node->val);


        if(node->left != NULL)
        {
            enqueue(&q, node->left);
        }


        if(node->right != NULL)
        {
            enqueue(&q, node->right);
        }
    }

    printf("\n");
}
//update node
void updateNode(struct TreeNode *root, int oldval, int newval)
{
    if(root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }
    struct Queue q;

    initQueue(&q);

    enqueue(&q, root);
    while(!isEmpty(&q))
    {
        struct TreeNode *node = dequeue(&q);
        if(node->val == oldval)
        {
            node->val = newval;

            printf("Updated successfully.\n");

            return;
        }
        if(node->left != NULL)
        {
            enqueue(&q, node->left);
        }
        if(node->right != NULL)
        {
            enqueue(&q, node->right);
        }
    }
    printf("Node with value %d not found.\n", oldval);
}
//to delete leaf node
void deleteLeafNode(struct TreeNode *root,
                    struct TreeNode *target)
{
    struct Queue q;

    initQueue(&q);

    enqueue(&q, root);


    while(!isEmpty(&q))
    {
        struct TreeNode *node = dequeue(&q);


        /* Check left child */

        if(node->left == target)
        {
            free(target);

            node->left = NULL;

            return;
        }
        else if(node->left != NULL)
        {
            enqueue(&q, node->left);
        }


        /* Check right child */

        if(node->right == target)
        {
            free(target);

            node->right = NULL;

            return;
        }
        else if(node->right != NULL)
        {
            enqueue(&q, node->right);
        }
    }
}


/* ==============================
   DELETE NODE
   ============================== */

void deleteNode(struct TreeNode **root, int target)
{
    if(*root == NULL)
    {
        printf("Tree is empty...\n");
        return;
    }


    /* If tree has only one node */

    if((*root)->left == NULL &&
       (*root)->right == NULL)
    {
        if((*root)->val == target)
        {
            free(*root);

            *root = NULL;

            printf("Node deleted successfully.\n");
        }

        return;
    }


    struct TreeNode *targetnode = NULL;
    struct TreeNode *deepestnode = NULL;

    struct Queue q;

    initQueue(&q);

    enqueue(&q, *root);


    /* Find target and deepest node */

    while(!isEmpty(&q))
    {
        deepestnode = dequeue(&q);


        if(deepestnode->val == target)
        {
            targetnode = deepestnode;
        }


        if(deepestnode->left != NULL)
        {
            enqueue(&q, deepestnode->left);
        }


        if(deepestnode->right != NULL)
        {
            enqueue(&q, deepestnode->right);
        }
    }
    //Target found 

    if(targetnode != NULL)
    {
// If target itself is a leaf 
        if(targetnode->left == NULL &&
           targetnode->right == NULL)
        {
            deleteLeafNode(*root, targetnode);

            printf("Node deleted successfully.\n");

            return;
        }
        targetnode->val = deepestnode->val;
        struct Queue q2;
        initQueue(&q2);
        enqueue(&q2, *root);

        while(!isEmpty(&q2))
        {
            struct TreeNode *temp = dequeue(&q2);


            /* Check left child */

            if(temp->left != NULL)
            {
                if(temp->left == deepestnode)
                {
                    free(temp->left);

                    temp->left = NULL;

                    printf("Node deleted successfully.\n");

                    return;
                }

                enqueue(&q2, temp->left);
            }
            /* Check right child */

            if(temp->right != NULL)
            {
                if(temp->right == deepestnode)
                {
                    free(temp->right);

                    temp->right = NULL;

                    printf("Node deleted successfully.\n");

                    return;
                }

                enqueue(&q2, temp->right);
            }
        }
    }
    else
    {
        printf("Node not found...\n");
    }
}

int main()
{
    struct TreeNode *root = NULL;

    int choice;
    int val;
    int oldval;
    int newval;

    do
    {
        printf("\n========== BINARY TREE MENU ==========\n");

        printf("1. Add Node\n");
        printf("2. Print Tree\n");
        printf("3. Update Node\n");
        printf("4. Delete Node\n");
        printf("5. Exit\n");

        printf("Choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch(choice)
        {
            case 1:
                printf("Enter value to add: ");
                scanf("%d", &val);
                addNode(&root, val);
                printf("Node added.\n");
                break;

            case 2:
                printf("Tree contents: ");
                readTree(root);
                break;

            case 3:
                printf("Enter exact value to update: ");
                scanf("%d", &oldval);
                printf("Enter the new value: ");
                scanf("%d", &newval);
                updateNode(root, oldval, newval);
                break;

            case 4:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                deleteNode(&root, val);
                break;

            case 5:
                printf("Exiting program...\n");
                break;

            default:

                printf("Invalid choice! Try again.\n");
        }

    } while(choice != 5);

    return 0;
}