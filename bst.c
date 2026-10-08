#include <stdio.h>
#include <stdlib.h>

//tree node

struct TreeNode
{
    int val;            //stores the actual value
    struct TreeNode *left;              //stores address of left child
    struct TreeNode *right;             //of right child
};

//queue for level order
struct QueueNode
{
    struct TreeNode *treeNode;       //stores the address of actual tree node
    struct QueueNode *next;          //stores the address of next queue node
};

//stack for non-recursive traversal-depth first traversal
struct StackNode
{
    struct TreeNode *treeNode;       //stores the address of actual tree node
    struct StackNode *next;          //stores the address of next stack node
};

//queue functions
void enqueue(struct QueueNode **front,struct QueueNode **rear,struct TreeNode *node)
{
    struct QueueNode *newnode;

    newnode=(struct QueueNode*)malloc(sizeof(struct QueueNode));      //memory allocation

    if(newnode==NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    newnode->treeNode=node;      //stores the address of tree node in queue
    newnode->next=NULL;          //initially the new queue node does not point to another queue node

    if(*rear==NULL)       //if rear is null then queue is empty
    {
        *front=newnode;
        *rear=newnode;
    }
    else
    {
        (*rear)->next=newnode;
        *rear=newnode;
    }
}

struct TreeNode* dequeue(struct QueueNode **front,struct QueueNode **rear)
{
    struct QueueNode *temp;
    struct TreeNode *node;       //stores the actual tree node address

    if(*front==NULL)       //if queue is empty there is nothing to return
    {
        return NULL;
    }

    temp=*front;
    node=temp->treeNode;       //get the tree node address from queue

    *front=(*front)->next;

    if(*front==NULL)
        *rear=NULL;

    free(temp);

    return node;       //returns the tree node
}

//stack functions
void pushStack(struct StackNode **top,struct TreeNode *node)
{
    struct StackNode *newnode;
    newnode=(struct StackNode*)malloc(sizeof(struct StackNode));      //memory allocation
    if(newnode==NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    newnode->treeNode=node;       //stores the node pointer
    newnode->next=*top;
    *top=newnode;
}

struct TreeNode* popStack(struct StackNode **top)
{
    struct StackNode *temp;
    struct TreeNode *node;

    if(*top==NULL)
    {
        return NULL;
    }

    temp=*top;
    node=temp->treeNode;

    *top=temp->next;

    free(temp);

    return node;       //returns the current top element
}

//to check for duplicate values
int valueExists(struct TreeNode *root,int value)
{
    struct TreeNode *current=root;

    while(current!=NULL)
    {
        if(current->val==value)
        {
            return 1;
        }
        if(value<current->val)
        {
            current=current->left;
        }
        else
        {
            current=current->right;
        }
    }
    return 0;
}

//add node
void addNode(struct TreeNode **root,int el)
{
    struct TreeNode *newnode;

    // Check for duplicate value
    if(valueExists(*root,el))
    {
        printf("Duplicate value cannot be accepted!\n");
        return;
    }

    newnode=(struct TreeNode*)malloc(sizeof(struct TreeNode));      //memory alloaction

    if(newnode==NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    newnode->val=el;       //stores the value
    newnode->left=NULL;       //initially new node has no left nd right
    newnode->right=NULL;

    //if tree is empty
    if(*root==NULL)         //tree is empty
    {
        *root=newnode;
        return;
    }

    struct TreeNode *current=*root;
    while(1)
    {
        //if value is smaller go to left
        if(el<current->val)
        {
            if(current->left==NULL)
            {
                current->left=newnode;
                return;
            }
            current=current->left;
        }

        //if value is greater go to right
        else
        {
            if(current->right==NULL)
            {
                current->right=newnode;
                return;
            }
           current=current->right;
        }
    }
}

//LEVEL ORDER / DISPLAY
void readTree(struct TreeNode *root)
{
    if(root==NULL)
    {
        printf("Tree is empty...\n");
        return;
    }

    struct QueueNode *front=NULL;
    struct QueueNode *rear=NULL;

    enqueue(&front,&rear,root);

    while(front!=NULL)
    {
        struct TreeNode *node=dequeue(&front,&rear);

        printf("%d ",node->val);            //prints node value

        if(node->left!=NULL)                //and then adds left nd right
        {
            enqueue(&front,&rear,node->left);
        }

        if(node->right!=NULL)
        {
            enqueue(&front,&rear,node->right);
        }
    }
    printf("\n");
}

//inorder traversal-non-recursive(left->root->right)
void inorderNonRecursive(struct TreeNode *root)
{
    struct StackNode *top=NULL;
    struct TreeNode *current=root;

    while(current!=NULL || top!=NULL)
    {
        while(current!=NULL)        //go to the leftmost end
        {
            pushStack(&top,current);
            current=current->left;
        }

        current=popStack(&top);
        printf("%d ",current->val);
        current=current->right;
    }
    printf("\n");
}

//preorder traversal-non-recursive(root->left->right)
void preorderNonRecursive(struct TreeNode *root)
{
    if(root==NULL)
    {
        return;
    }
    struct StackNode *top=NULL;

    pushStack(&top,root);

    while(top!=NULL)
    {
        struct TreeNode *node=popStack(&top);

        printf("%d ",node->val);

        if(node->right!=NULL)       //right first because stack is LIFO
        {
            pushStack(&top,node->right);
        }
        if(node->left!=NULL)
        {
            pushStack(&top,node->left);
        }
    }
    printf("\n");
}

//postorder traversal-non-recursive(left->right->root)
void postorderNonRecursive(struct TreeNode *root)
{
    if(root==NULL)
    {
        return;
    }

    struct StackNode *top1=NULL;
    struct StackNode *top2=NULL;

    pushStack(&top1,root);

    while(top1!=NULL)
    {
        struct TreeNode *node=popStack(&top1);

        pushStack(&top2,node);

        if(node->left!=NULL)
        {
            pushStack(&top1,node->left);
        }

        if(node->right!=NULL)
        {
            pushStack(&top1,node->right);
        }
    }

    while(top2!=NULL)
    {
        struct TreeNode *node=popStack(&top2);
        printf("%d ",node->val);
    }
    printf("\n");
}

//update node
void updateNode(struct TreeNode **root,int oldval,int newval)
{
    struct TreeNode *current=*root;

    if(*root==NULL)
    {
        printf("Tree is empty.\n");
        return;
    }

    //search old value
    while(current!=NULL)
    {
        if(current->val==oldval)
        {
            break;
        }
        if(oldval<current->val)
        {
            current=current->left;
        }
        else
        {
            current=current->right;
        }
    }
    if(current==NULL)
    {
        printf("Node with value %d not found.\n",oldval);
        return;
    }

    //check whether new value already exists
    current=*root;
    while(current!=NULL)
    {
        if(current->val==newval)
        {
            printf("New value already exists! Update not allowed.\n");
            return;
        }

        if(newval<current->val)
        {
            current=current->left;
        }
        else
        {
            current=current->right;
        }
    }

    //delete old value first
    deleteNode(root,oldval);

    //insert new value
    addNode(root,newval);
}

//delete node
void deleteNode(struct TreeNode **root,int target)   //**root is a pointer to a root pointer
{
    if(*root==NULL)
    {
        printf("Tree is empty...\n");
        return;
    }

    struct TreeNode *current=*root;
    struct TreeNode *parent=NULL;

    //search for target node
    while(current!=NULL && current->val!=target)  //keep searching until current is null or target is found
    {
        parent=current;
        if(target<current->val)
        {
            current=current->left;
        }
        else
        {
            current=current->right;
        }
    }

    //node not found
    if(current==NULL)
    {
        printf("Node not found...\n");
        return;
    }

    //Case 1: node has no child
    if(current->left==NULL && current->right==NULL)   //leaf node

    {
        if(parent==NULL)
        {
            *root=NULL;
        }
        else if(parent->left==current)
        {
            parent->left=NULL;
        }
        else
        {
            parent->right=NULL;
        }

        free(current);

        printf("Node deleted successfully.\n");
    }

    //Case 2: node has only right child

    else if(current->left==NULL)
    {
        if(parent==NULL)
        {
            *root=current->right;
        }
        else if(parent->left==current)
        {
            parent->left=current->right;
        }
        else
        {
            parent->right=current->right;
        }

        free(current);

        printf("Node deleted successfully.\n");
    }

    //Case 3: node has only left child
    else if(current->right==NULL)
    {
        if(parent==NULL)
        {
            *root=current->left;
        }
        else if(parent->left==current)
        {
            parent->left=current->left;
        }
        else
        {
            parent->right=current->left;
        }

        free(current);

        printf("Node deleted successfully.\n");
    }

    //Case 4: node has two children
    else
    {
        //find inorder successor
        struct TreeNode *successor=current->right;
        struct TreeNode *successorParent=current;

        while(successor->left!=NULL)
        {
            successorParent=successor;
            successor=successor->left;
        }

        current->val=successor->val;

        if(successorParent->left==successor)
        {
            successorParent->left=successor->right;
        }
        else
        {
            successorParent->right=successor->right;
        }

        free(successor);

        printf("Node deleted successfully.\n");
    }
}

int main()
{
    struct TreeNode *root=NULL;            //initially tree is empty

    int choice;
    int val;
    int oldval;
    int newval;
    char chr;


    do
    {
        printf("     \n BINARY SEARCH TREE MENU\n");

        printf("1. Add Node\n");
        printf("2. Print Tree (Level Order)\n");
        printf("3. Update Node\n");
        printf("4. Delete Node\n");

        printf("\n--- Non-Recursive Traversals ---\n");

        printf("5. Inorder - Non-Recursive\n");
        printf("6. Preorder - Non-Recursive\n");
        printf("7. Postorder - Non-Recursive\n");

        printf("\n8. Exit\n");

        printf("====================================\n");
        printf("Choice: ");

        if(scanf("%d",&choice)!=1)
        {
            printf("Invalid input! Please enter a number.\n");
            while(getchar()!='\n');        //clears the invalid characters from i/p
            continue;
        }

        switch(choice)
        {
            case 1:

                printf("Enter value to add(number only): ");

                if(scanf("%d",&val)!=1)
                {
                    printf("Invalid input! Please enter a number only.\n");

                    while(getchar()!='\n');

                    break;
                }

                chr=getchar();

                if(chr!='\n')
                {
                    printf("Invalid input! Spaces/special characters are not allowed.\n");
                    while(getchar()!='\n');
                    break;
                }
                addNode(&root,val);
                break;

            case 2:
                printf("Tree contents: ");
                readTree(root);
                break;

            case 3:
                printf("Enter exact value to update: ");
                scanf("%d",&oldval);
                printf("Enter the new value: ");
                scanf("%d",&newval);
                updateNode(&root,oldval,newval);
                break;

            case 4:
                printf("Enter value to delete: ");
                scanf("%d",&val);
                deleteNode(&root,val);
                break;

            case 5:
                if(root==NULL)
                {
                    printf("Tree is empty.\n");
                }
                else
                {
                    printf("Inorder (Non-Recursive):\n ");
                    inorderNonRecursive(root);
                }
                break;

            case 6:
                if(root==NULL)
                {
                    printf("Tree is empty.\n");
                }
                else
                {
                    printf("Preorder (Non-Recursive):\n ");
                    preorderNonRecursive(root);
                }
                break;

            case 7:
                if(root==NULL)
                {
                    printf("Tree is empty.\n");
                }
                else
                {
                    printf("Postorder (Non-Recursive):\n ");
                    postorderNonRecursive(root);
                }
                break;

            case 8:
                printf("Exiting program...\n");
                break;

            default:

                printf("Invalid choice! Try again.\n");
        }

    } while(choice!=8);            //keep executing until user inputs 8

    return 0;
}