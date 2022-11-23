// AVL.C 
//
// Code for ELEC278 Lab 4.  Some code has already been implemented.
// You will develop your own code - look for the comments that say:
// "Your code goes here";
//


/* --README--------------------------------------------------------------------
Source code used for teaching purposes in course:
ELEC278, Queen's University, Kingston, Fall semester 2022.
This code is provided without warranty of any kind. It is the responsibility
of the user to determine the correctness and the usefulness of this code for
any purpose.

All rights reserved. This code is intended for students registered in the
course and the semester listed above.

See LICENCE.MD for restrictions on the use of this code.
---------------------------------------------------------------------------- */


#include <stdio.h>
#include "bintree.h"
#include "avl.h"



void printTree(Node* root)
// Print representation of tree. We make an assumption, because tree nodes
// actually have pointer to data, not actual data.  So assume that it is a
// pointer to an integer.
{
	printf("{");		// Tree starts with an opening curly bracket
	// then value of root node
	printf("(%d,%d)", root->key, *(int*) root->value);
						// need to cast void pointer actual data type
	printf(",");		// children come next

	// left child. If NULL it will just print two empty braces,
	// otherwise it prints whole left tree.
	if (root->leftChild) {
		printTree(root->leftChild);
	} else
		printf("{}");
	// separate left child from right child
	printf(",");
	// right child. If NULL it will just print two empty braces,
	// otherwise it prints whole right tree.
	if (root->rightChild) {
		printTree(root->rightChild);
	} else
		printf("{}");
	printf("}");	// Tree ends with closing curly bracket
}//printTree()

//=============================================================================
// ALTERNATE IMPLEMENTATION OF PRINTTREE - FOR YOUR REVIEW.
//    YOU MAY IGNORE THIS.

void printTree2(Node* root)
// Print representation of tree. We make an assumption, because tree nodes
// actually have pointer to data, not actual data.  So assume that it is a
// pointer to an integer.
{
	if (root == NULL)	{
		// printing an empty tree
		printf("{}");
	} else	{
		// printing non-empty tree
		printf("{");		// Tree starts with an opening curly bracket
		// then value of root node
		printf("(%ld,%d)", (long) root->key, *(int*) root->value);
							// need to cast void pointer actual data type
		printf(",");		// children come next

		// left child.
		printTree(root->leftChild);
		// separate left child from right child
		printf(",");
		// right child.
		printTree(root->rightChild);
		printf("}");	// Tree ends with closing curly bracket
		}
}//printTree2()
//=============================================================================

int maxint(int a, int b){
    return (a>=b) ? a : b;
}

void insertAVL (Key k, void *v, Tree *t)
// Add new data item to tree.  Use two data components - key and actual data -
// to create new node and insert node in appropriate place.
{
	// Check for mistakes, including verification of tree type
	if ((t == NULL) || (t->tt != AVL))	return;
	//printf("Insert %d into AVL\n", k);
	// Check if tree empty - if so, insert first node
	if (t->root == NULL) {
		Node *n = initNode(k, v);
		n->height = 0;
		t->root = n;
	} else	{
		t->root = insertNodeAVL(k, v, t->root);
		}
	return;
}//insert()


Node* rotateRight(Node* root){
	printf("Rotate Right\n");
    Node *lc;
    lc = root->leftChild;
    root->leftChild = lc->rightChild;
    lc->rightChild = root;
    root->height=calcHeight(root);
    lc->height=calcHeight(lc);

	return lc;
}//rotateRight()


Node* rotateLeft(Node* root){
	printf("Rotate Left\n");

    Node *rc;
    rc=root->rightChild;
    root->rightChild=rc->leftChild;
    rc->leftChild = root;
    root->height=calcHeight(root);
    rc->height=calcHeight(rc);
    return rc;

}//rotateLeft()

int getBalanceFactor(Node* root)
{
//---<SNIP>---
    int lh = -1, rh = -1;
    if(root==NULL)
        return(0);
    if(root->leftChild==NULL)
        lh=-1;
    else
        lh=root->leftChild->height;
    if(root->rightChild==NULL)
        rh=-1;
    else
        rh=root->rightChild->height;
    return lh-rh;
}//getBalanceFactor()


int calcHeight(Node* root){
    int lh = -1, rh = -1;
    if(root==NULL)
        return(0);
    if(root->leftChild==NULL)
        lh=-1;
    else
        lh=root->leftChild->height;
    if(root->rightChild==NULL)
        rh=-1;
    else
        rh=root->rightChild->height;

	return maxint(rh, lh) + 1;
}//calcHeight();


Node* rebalance(Node* root){
    int bf = getBalanceFactor(root);
    if (bf > 1){ // tree is left heavy
        int lbf = getBalanceFactor(root->leftChild); //balance factor of left child
        if (lbf >= 1) //if it's left heavy, rotate right
            return rotateRight(root);
        else if (lbf <= -1){ //if it's left then right heavy, rotate left then right
            root->leftChild = rotateLeft(root->leftChild);
            return rotateRight(root);
        }
    }

    if (bf < -1){ // tree is right heavy
        int rbf = getBalanceFactor(root->rightChild);
        if (rbf <= -1) //if it's right heavy, rotate left
            return rotateLeft(root);
        else if (rbf >= 1){ //if it's right heavy then left heavy, rotate right then left
            root->rightChild = rotateRight(root->rightChild);
            return rotateLeft(root);
        }
    }
    return root;
}//rebalance()


Node* insertNodeAVL(Key k, void *v, Node *root)
// Build new node and insert into (non-empty) tree. Check if insertion has
// created imbalance and rebalance if necessary.
{
	if (root==NULL) {
		Node *n = initNode(k, v);
		n->height = 0;
		return n;
		}
	if (k < root->key) {
		root->leftChild = insertNodeAVL(k, v, root->leftChild);
		root->height = calcHeight(root);
	} else if (k > root->key) {
		root->rightChild = insertNodeAVL(k, v, root->rightChild);
		root->height = calcHeight(root);
		}
	// Note - ignored equal case - should not occur.
	return rebalance(root);
}//insertNode()


void inOrderT(Node* root)
// In order traversal of tree displaying contents
{
	if (root) {
		inOrderT(root->leftChild);
		printf("%d(h=%d,bf=%d) - ", root->key, root->height,getBalanceFactor(root));
		inOrderT(root->rightChild);
		}
}//inOrderT()

Node * minValueNode(Node* node)
{
    Node* current = node;
    /* loop down to find the leftmost leaf */
    while (current->leftChild != NULL)
        current = current->leftChild;

    return current;
}

