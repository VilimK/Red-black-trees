#include<stdio.h>
#include<stdlib.h>

///node structure
struct node{
    int data; ///data
    char color; ///color of node
    struct node *left, *right, *parent;///pripadni pokazivaci
};



///Function of node transplantation which is necessary
///to delete node and repair tree structure after deletion
void Transplant(struct node **root,struct node *u, struct node *v){
	if(u->parent==NULL){
		(*root)=v;
	}
	else if(u==u->parent->left){
		u->parent->left=v;
	}
	else{
		u->parent->right=v;
	}

	v->parent=u->parent;
}



struct node *FindMin(struct node *x){
    while(x->left!=NULL){
        x=x->left;
    }
    return x;
}

struct node *FindMax(struct node *x){
    while(x->right!=NULL){
        x=x->right;
    }
    return x;
}

///Lijeva rotacija - funkcija koja nam je potrebna za obavljanje
///popravka Crveno-crnih svojstava nakon funkcije insert

///Left rotation - function that is necessary for reparation of
///Red-black tree properties after inserting/deleting certain node
void LRotation(struct node **root,struct node *a)
{
    if (!a || !a->right){
        return ;
    }
    struct node *b=a->right;


    a->right=b->left;


    if (a->right!=NULL){
        a->right->parent=a;
    }

    b->parent=a->parent;

    if (a->parent==NULL){
        (*root)=b;
    }
    else if (a==a->parent->left){
        a->parent->left=b;
    }
    else{
        a->parent->right=b;
    }
    b->left=a;

    a->parent=b;
}


///Right rotation, similar as left rotation
void RRotation(struct node **root,struct node *a)
{
    if (!a || !a->left){
        return ;
    }
    struct node *b=a->left;
    a->left=b->right;
    if (b->right!=NULL){
        b->right->parent=a;
    }
    b->parent=a->parent;
    if (b->parent==NULL){
        (*root)=b;
    }
    else if (a==a->parent->left){
        a->parent->left=b;
    }
    else{
        a->parent->right=b;
    }
    b->right=a;
    a->parent=b;
}


///Repair function is called after inserting a node in tree, it
/// fixes tree properties
void Repair(struct node **root,struct node *z)
{
    while (z!=(*root) && z!=(*root)->left && z!=(*root)->right && z->parent->color=='R')
    {
        struct node *uncle;
        if (z->parent && z->parent->parent && z->parent==z->parent->parent->left){
            uncle=z->parent->parent->right;
        }
        else{
            uncle=z->parent->parent->left;
        }
        if (!uncle){
            z=z->parent->parent;
        }
        else if (uncle->color=='R'){
            uncle->color='B';
            z->parent->color='B';
            z->parent->parent->color='R';
            z = z->parent->parent;
        }


        else
        {
            if (z->parent==z->parent->parent->left && z==z->parent->left){
                char c=z->parent->color ;
                z->parent->color=z->parent->parent->color;
                z->parent->parent->color=c;
                RRotation(root,z->parent->parent);
            }
            if (z->parent && z->parent->parent && z->parent==z->parent->parent->left && z==z->parent->right){
                char c=z->color ;
                z->color=z->parent->parent->color;
                z->parent->parent->color=c;
                LRotation(root,z->parent);
                RRotation(root,z->parent->parent);
            }

            if (z->parent && z->parent->parent && z->parent == z->parent->parent->right && z == z->parent->right){
                char c=z->parent->color ;
                z->parent->color= z->parent->parent->color;
                z->parent->parent->color=c;
                LRotation(root,z->parent->parent);
            }

            if (z->parent && z->parent->parent && z->parent==z->parent->parent->right && z==z->parent->left){
                char c=z->color ;
                z->color=z->parent->parent->color;
                z->parent->parent->color=c;
                RRotation(root,z->parent);
                LRotation(root,z->parent->parent);
            }
        }
    }
    (*root)->color='B';
}
void InsertNode(struct node **root, int data)
{

    struct node *z = (struct node*)malloc(sizeof(struct node));
    z->data=data;
    z->left=z->right=z->parent=NULL;


    if ((*root)==NULL){
        z->color='B';
        (*root)=z;
    }
    else{
        struct node *y=NULL;
        struct node *x=(*root);

        while (x!=NULL){
            y=x;
            if (z->data < x->data){
                x=x->left;
            }
            else{
                x=x->right;
            }
        }
        z->parent=y;
        if (z->data > y->data){
            y->right=z;
        }
        else{
            y->left=z;
        }
        z->color='R';

        Repair(root,z);
    }
}


struct node* FindNode(struct node *root, int x){
    if(root==NULL || root->data==x){
        return root;
    }
    else if(x>root->data){
        return FindNode(root->right,x);
    }
    else{
        return FindNode(root->left,x);
    }
}


///Inorder traversal function
void inorder(struct node *root){
    static int l=0;
    if (root==NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    if (root->data < l){
        printf("\n");
    }
    l = root->data;
    inorder(root->right);
}



void DeleteRepair(struct node **root, struct node *x){
    struct node *w;
    while(x!=(*root) && x->color=='B'){
        if(x==x->parent->left){

            w=x->parent->right;

            if(w->color=='R'){

                w->color='B';
                x->parent->color='R';
                LRotation(root,x->parent);
                w=x->parent->right;

            }
            if(w->left->color=='B' && w->right->color=='B'){

                w->color='R';
				x->parent->color='B';
				x = x->parent;

            }
            else{

                if(w->right->color=='B'){
					w->color='R';
					w->left->color='B';
                    RRotation(root,w);
					w = x->parent->right;

				}

				w->color=x->parent->color;
				x->parent->color='B';
				x->right->color='B';
				LRotation(root,x->parent);
				x=(*root);
            }

        }
        else{
            w=x->parent->left;
            if(w->color=='R'){
                w->color='B';
                x->parent->color='B';
                RRotation(root,x->parent);
                w=x->parent->left;
            }
            if(w->left->color=='B' && w->right->color=='b'){
                w->color = 'R';
				x->parent->color = 'B';
				x = x->parent;
            }
            else{
                if(w->left->color=='B'){
                    w->color='R';
                    w->right->color = 'B';
					LRotation(root,w);
					w = x->parent->left;
                }
                w->color = x->parent->color;
				x->parent->color = 'B';
				w->left->color = 'B';
				RRotation(root,x->parent);
				x = (*root);

            }

        }
    }
    x->color='B';
}






void DeleteNode(struct node **root, int data){
    struct node *nodeToBeDeleted=FindNode(*root,data);
    struct node *x,*y;
    if(nodeToBeDeleted==NULL){
        return;
    }
    char orgColor=nodeToBeDeleted->color;
    if(nodeToBeDeleted->left==NULL){
        x=nodeToBeDeleted->right;
        Transplant(root,nodeToBeDeleted,x);
    }
    else if(nodeToBeDeleted->right==NULL){
        x=nodeToBeDeleted->left;
        Transplant(root,nodeToBeDeleted,x);
    }
    else{
        y=FindMin(nodeToBeDeleted->right);
        orgColor=y->color;
        x=y->right;
        if(y==nodeToBeDeleted->right || y==nodeToBeDeleted->left){
            x->parent=y;
        }
        else{
            Transplant(root,y,y->right);
        }
        Transplant(root,nodeToBeDeleted,y);
        y->color=orgColor;
    }
    if(orgColor=='B'){
        DeleteRepair(root,x);
    }



}




