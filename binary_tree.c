#include <stdio.h>
#include <stdlib.h>

//tree node
struct TreeNode
{
    int val;            //stores the actual value
    struct TreeNode *left;              //stores address of left child
    struct TreeNode *right;                 //of right child
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
void enqueue(struct QueueNode **front,struct QueueNode **rear,struct TreeNode *node)     //to add node to the queue
{           //address of front,rear and address of the tree node we want to insert
    struct QueueNode *newnode;
    newnode=(struct QueueNode*)malloc(sizeof(struct QueueNode));      //memory allocation
    if(newnode==NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    newnode->treeNode=node;      //stores the address of tree node in queue
    newnode->next=NULL;         //initially the new queue node does not point to another queue node
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
    struct TreeNode *node;      //stores the actual tree node address

    if(*front==NULL)     //if queue is empty there is nothing to return
    {
        return NULL;
    }
    temp=*front;
    node=temp->treeNode;       //get the tree node address from queue
    *front=(*front)->next;
    if(*front==NULL)
        *rear=NULL;
    free(temp);
    return node;    //returns the tree node
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
    newnode->treeNode=node;     //stores the node pointer
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
    return node;    //returns the current top element
}

//to check for duplicate values
int valueExists(struct TreeNode *root,int value)
{
    if(root==NULL)         //if root is only null tree is empty
        return 0;

    struct QueueNode *front=NULL;
    struct QueueNode *rear=NULL;

    enqueue(&front,&rear,root);

    while(front!=NULL)         //traverse until queue is empty
    {
        struct TreeNode *node=dequeue(&front,&rear);

        if(node->val==value)
            return 1;

        if(node->left!=NULL)
            enqueue(&front,&rear,node->left);

        if(node->right!=NULL)
            enqueue(&front,&rear,node->right);
    }

    return 0;
}

//add node
void addNode(struct TreeNode **root,int el)   //bcoz this func may need to change the actual root pointer
{
    // Check for duplicate value
    if(valueExists(*root,el))
    {
        printf("Duplicate value cannot be accepted!\n");
        return;
    }

    struct TreeNode *newnode;
    newnode=(struct TreeNode*)malloc(sizeof(struct TreeNode));      //memory alloaction

    if(newnode==NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    newnode->val=el;     //stores the value
    newnode->left=NULL;      //initially new node has no left nd right
    newnode->right=NULL;

    //if tree is empty
    if(*root==NULL)         //tree is empty
    {
        *root=newnode;
        return;
    }

    struct QueueNode *front=NULL;
    struct QueueNode *rear=NULL;

    enqueue(&front,&rear,*root);

    while(front!=NULL)
    {
        struct TreeNode *node=dequeue(&front,&rear);

        //check left child
        if(node->left!=NULL)
        {
            enqueue(&front,&rear,node->left);   //if left child exists continue searching
        }
        else
        {
            node->left=newnode;    //if not exists then insert new node
            return;
        }

        //check right child--same way
        if(node->right!=NULL)
        {
            enqueue(&front,&rear,node->right);
        }
        else
        {
            node->right=newnode;
            return;
        }
    }
}

//LEVEL ORDER / DISPLAY
void readTree(struct TreeNode *root)        //display the tree using inorder traversal
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

        if(node->left!=NULL)               //and then adds left nd right
        {
            enqueue(&front,&rear,node->left);
        }
        if(node->right!=NULL)
        {
            enqueue(&front,&rear,node->right);
        }
    }

    printf("\n");           //root->left+right->next level
}

//inorder traversal-recursive(left->root->right)
void inorderRecursive(struct TreeNode *root)
{
    if(root==NULL)
    {
        return;
    }
    inorderRecursive(root->left);            //go left
    printf("%d ",root->val);                //print root
    inorderRecursive(root->right);           //go right
}

//preorder traversal-recursive(root->left->right)
void preorderRecursive(struct TreeNode *root)
{
    if(root==NULL)
    {
        return;
    }
    printf("%d ",root->val);             //prints the root first
    preorderRecursive(root->left);           //then goes left nd print left
    preorderRecursive(root->right);         //then goes right nd print right
}

//postorder traversal-recursive(left->right->root)
void postorderRecursive(struct TreeNode *root)
{
    if(root==NULL)
    {
        return;
    }
    postorderRecursive(root->left);    //first left
    postorderRecursive(root->right);     //then right
    printf("%d ",root->val);      //then prints root value
}

//inorder traversal- non-recursive(left->root->right)
void inorderNonRecursive(struct TreeNode *root)
{
    struct StackNode *top=NULL;
    struct TreeNode *current=root;

    while(current!=NULL || top!=NULL)   //iterate until the stack becomes empty or there is either a current node
    {
        while(current!=NULL)    //iterate until node/current is null to the leftmost possible
        {
            pushStack(&top,current);
            current=current->left;
        }
        current=popStack(&top);    //get node from stack
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
        struct TreeNode *node=popStack(&top);  //first pops node and print it
        printf("%d ",node->val);

        if(node->right!=NULL)      //right first becoz stack is LIFO
        {                       //Like if say i push 3 2 then 2 is at the top so it gets prints/processed first
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
void updateNode(struct TreeNode *root,int oldval,int newval)
{
    if(root==NULL)
    {
        printf("Tree is empty.\n");
        return;
    }

    struct QueueNode *front=NULL;
    struct QueueNode *rear=NULL;

    enqueue(&front,&rear,root);

    while(front!=NULL)
    {
        struct TreeNode *node=dequeue(&front,&rear);

        if(node->val==oldval)            //if node value matches the old value
        {
            node->val=newval;            //then update it
            printf("Updated successfully.\n");
            return;
        }
        if(node->left!=NULL)
        {
            enqueue(&front,&rear,node->left);
        }
        if(node->right!=NULL)
        {
            enqueue(&front,&rear,node->right);
        }
    }
    printf("Node with value %d not found.\n",oldval);
}

//delete leaf node
void deleteLeafNode(struct TreeNode *root,
                    struct TreeNode *target)
{
    struct QueueNode *front=NULL;
    struct QueueNode *rear=NULL;

    enqueue(&front,&rear,root);

    while(front!=NULL)
    {
        struct TreeNode *node=dequeue(&front,&rear);

        /* Check left child */
        if(node->left==target)
        {
            free(target);
            node->left=NULL;
            return;
        }
        else if(node->left!=NULL)
        {
            enqueue(&front,&rear,node->left);
        }

        //check for right child
        if(node->right==target)
        {
            free(target);
            node->right=NULL;
            return;
        }
        else if(node->right!=NULL)
        {
            enqueue(&front,&rear,node->right);
        }
    }
}

//delete node
void deleteNode(struct TreeNode **root,int target)
{
    if(*root==NULL)
    {
        printf("Tree is empty...\n");
        return;
    }

    /* If tree has only one node */
    if((*root)->left==NULL &&        //checks whether has no left nd no right child
       (*root)->right==NULL)
    {
        if((*root)->val==target)     //checks if the single node is the target value
        {
            free(*root);     //if yes free the dynamically allocated memory
            *root=NULL;
            printf("Node deleted successfully.\n");
        }
        else
        {
            printf("Node not found...\n");
        }
        return;
    }

    struct TreeNode *targetnode=NULL;      //targetnode stores the address of the node that user wants to delete
    struct TreeNode *deepestnode=NULL;
    struct TreeNode *parentOfDeepest=NULL;     //it stores the parent of deepest node

    struct QueueNode *front=NULL;       //for level order traversal
    struct QueueNode *rear=NULL;       //queue initialization

    enqueue(&front,&rear,*root);           //put root into queue

    //finds target node,deepest node and parent of deepest node
    while(front!=NULL)
    {
        struct TreeNode *current=dequeue(&front,&rear);          //everytime we dequeue a node,deepest node changes

        if(current->val==target)     //check whether current node is target value
        {
            targetnode=current;
        }

        if(current->left!=NULL)
        {
            parentOfDeepest=current;
            deepestnode=current->left;
            enqueue(&front,&rear,current->left);
        }

        if(current->right!=NULL)
        {
            parentOfDeepest=current;
            deepestnode=current->right;
            enqueue(&front,&rear,current->right);
        }
    }

    /* Target found */
    if(targetnode!=NULL)
    {
        /* If target itself is a leaf */
        if(targetnode->left==NULL &&
           targetnode->right==NULL)
        {
            deleteLeafNode(*root,targetnode);     //we can directly delete leaf node by calling its function
            printf("Node deleted successfully.\n");
            return;
        }

        //copy target value with deepest node value
        targetnode->val=deepestnode->val;

        if(parentOfDeepest->left==deepestnode)
        {
            free(deepestnode);
            parentOfDeepest->left=NULL;
        }
        else
        {
            free(deepestnode);
            parentOfDeepest->right=NULL;
        }

        printf("Node deleted successfully.\n");
    }
    else                 //if target node is null i.e. not found in the tree then print node not found
    {
        printf("Node not found...\n");
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

    do             //menu should execute atleast once
    {
        printf("     \n BINARY TREE MENU\n");
        printf("1. Add Node\n");
        printf("2. Print Tree (Level Order)\n");
        printf("3. Update Node\n");
        printf("4. Delete Node\n");

        printf("\n--- Non-Recursive Traversals ---\n");
        printf("5. Inorder - Non-Recursive and Recursive\n");
        printf("6. Preorder - Non-Recursive and Recursive\n");
        printf("7. Postorder - Non-Recursive and Recursive\n");

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
                    while(getchar()!='\n');         //scanf cannot accept abc so this removes everything until \n
                    break;
                }
                chr=getchar();
                if(chr!='\n'){
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
                updateNode(root,oldval,newval);
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
                    printf("Inorder (Non-Recursive)\n: ");
                    inorderNonRecursive(root);
                    printf("(Recursive)\n:");
                    inorderRecursive(root);
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
                    printf("(Recursive):\n");
                    preorderRecursive(root);
                }
                break;

            case 7:
                if(root==NULL)
                {
                    printf("Tree is empty.\n");
                }
                else
                {
                    printf("Postorder (Non-Recursive): \n");
                    postorderNonRecursive(root);
                    printf("(Recursive):\n");
                    postorderRecursive(root);
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