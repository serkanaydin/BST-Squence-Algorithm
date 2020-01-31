#include <stdio.h>
#include <stdlib.h>
FILE*  fp;
struct bst{
    int value;
    struct bst*left,*right;
};
struct possibleNodes{
    struct bst* node;
    struct possibleNodes* next;

};
typedef struct possibleNodes POSSIBLENODES;
typedef struct possibleNodes* possiblePtr;
typedef struct bst BST;
typedef struct bst* bstPtr;
int total=0;
bstPtr newNode(double num)
{
    bstPtr temp =  malloc(sizeof(BST));
    temp->value = num;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
bstPtr insert(bstPtr  p, double key)
{
    if (p == NULL){
      bstPtr node= newNode(key);
        return node;}
    if (key < p->value){
        p->left  = insert(p->left, key);
    }
    else if (key > p->value){
        p->right = insert(p->right, key);
    }
    return p;
}
void getChildren(bstPtr child[],bstPtr node){
    if(node->left!=NULL && node->right!=NULL){
        child[0]=node->left;
        child[1]=node->right;
        return ;
    }
    else if(node->left!=NULL && node->right==NULL){
        child[0]=node->left;
        child[1]=NULL;
        return ;
    }
    else if(node->left==NULL && node->right!=NULL){
        child[0]=node->right;
        child[1]=NULL;
        return ;
    }
    else{
        child[0]=NULL;
        child[1]=NULL;
    }
}
int getLengthPossibleNodes(possiblePtr root){
    int i=0;
    possiblePtr temp=root;
    if(temp==NULL)
        return -1;
    while(temp->next!=NULL){
        temp=temp->next;
        i++;
    }
    return i;
}
possiblePtr insertChildren(possiblePtr root,bstPtr child[]){
if(child[0] == NULL && child[1]==NULL)
    return root;
    possiblePtr newRoot = malloc(sizeof(POSSIBLENODES));
    newRoot->node=child[0];
    newRoot->next=NULL;
    if(child[1]!=NULL){
        newRoot->next=malloc(sizeof(POSSIBLENODES));
        newRoot->next->node=child[1];
        newRoot->next->next=NULL;
    }
    else newRoot->next=NULL;
    if(root==NULL)
        return newRoot;
    possiblePtr temp=newRoot;

    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=root;
    return  newRoot;
}
possiblePtr searchLinkList(possiblePtr root,int i){
    possiblePtr  temp;
    temp =root;
  while(i>0){
      if(temp->next!=NULL)
      temp= temp->next;
      else return NULL;
      i--;
  }
  return temp;
}
void createPermutations(possiblePtr root,int str[],int index,int j){
if(root==NULL){
total++;
    for(int i=0;i<j;i++){
        fprintf(fp,"%d ",str[i]);
    }
    fprintf(fp,"\n");
    fflush(fp);
   return;
}

int newIndex =index+1;
int lenPossibility=  getLengthPossibleNodes(root);
for(int i=0;i<=lenPossibility;i++){
    possiblePtr nodePossiblePtr = searchLinkList(root,i);
    bstPtr node = nodePossiblePtr->node;
    possiblePtr temp=root;
    if(temp==nodePossiblePtr){
        root=root->next;
    }
    else {while(temp->next!=nodePossiblePtr){
        temp=temp->next;
    }
    temp->next=nodePossiblePtr->next;
   }
    bstPtr  child[2];
    getChildren(child,node);
    possiblePtr currentPossibilities = insertChildren(root,child);
    str[newIndex] =node->value;
    createPermutations(currentPossibilities,str,newIndex,j);
    if(root==NULL)
    root=temp;
    else if(nodePossiblePtr->next!=NULL &&nodePossiblePtr->next==root){
     root = nodePossiblePtr;
    }
    else {
        possiblePtr nextPtr = NULL;
        possiblePtr prev = searchLinkList(root, i - 1);
        if (prev->next != NULL) {
            nextPtr = prev->next;
        }
        prev->next=nodePossiblePtr;
        if(nextPtr!=NULL)
            nodePossiblePtr->next=nextPtr;
        else nodePossiblePtr->next=NULL;
    }
}
}
void inorder(bstPtr node){
    if(node!=NULL){
        printf("%d ",node->value);
        inorder(node->left);
        inorder(node->right);
    }
}
int main() {
    fp=fopen("./output.txt","w");
    bstPtr root=NULL;
    int value;
    int i=0;
    printf("Enter integer values to build tree. If you want to stop to enter value enter '-1'\n");
       scanf("%d",&value);
       while(value!=-1){
        if(root==NULL) {
            root = malloc(sizeof(BST));
            root->value = value;
            root->right = NULL;
            root->left = NULL;

       }
        else
                insert(root,value);
        i++;
           scanf("%d",&value);
       }
       printf("BST tree inorder traversal : ");
       inorder(root);
       printf("\n");
       printf("Sequences will be printed to ./output.txt \n");
   int str[i];
   str[0]=root->value;
   bstPtr child[2];
   getChildren(child,root);
   possiblePtr possibleRoot = insertChildren(NULL,child);
   createPermutations(possibleRoot,str,0,i);
   fclose(fp);
   printf("Total sequences number : %d",total);
   return 0;
}
