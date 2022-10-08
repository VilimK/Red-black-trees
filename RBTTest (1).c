#include <stdio.h>
#include <stdlib.h>
#include "RedBlackTree.h"




int main(void){

 struct node *root = NULL;
    InsertNode(&root,10);
    InsertNode(&root,20);
    InsertNode(&root,40);
    InsertNode(&root,30);
    InsertNode(&root,50);
    InsertNode(&root,35);
    InsertNode(&root,25);
    InsertNode(&root,37);
    InsertNode(&root,130);
    InsertNode(&root,150);
    InsertNode(&root,135);
    InsertNode(&root,125);
    InsertNode(&root,137);
    InsertNode(&root,1);

    printf("\n");
    printf("Inorder traversal:\n");
    inorder(root);
    printf("\n");
    DeleteNode(&root,130);
    DeleteNode(&root,10);
    DeleteNode(&root,150);
    printf("Inorder traversal after deleting certain nodes:\n");
    inorder(root);
    printf("\n");
    printf("Minimum node: ");
    printf("%d\n", FindMin(root)->data);
    printf("Maximum node: ");
    printf("%d\n", FindMax(root)->data);
return 0;}
