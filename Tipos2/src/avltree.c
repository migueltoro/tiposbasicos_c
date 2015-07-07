/*
 * avltree.c


 *
 *  Created on: May 5, 2015
 *      Author: Miguel Toro
 */


#include "avltree.h"

node_t nd_create(void * k);
node_t nd_insert(node_t p, void * k, comparator(c), boolean * inserted); // insert k key in a tree with p root
node_t nd_find(node_t p, void * k, comparator(c)); // find k key in a tree with p root or NULL if not found
node_t nd_findmin(node_t p); // find a node with minimal key in a p tree
node_t nd_findmax(node_t p); // find a node with maximal key in a p tree
node_t nd_removemin(node_t p); // deleting a node with minimal key from a p tree
node_t nd_removemax(node_t p); // deleting a node with maximal key from a p tree
node_t nd_remove_key(node_t p, void * k, comparator(c), boolean * removed);  // deleting k key from p tree
void nd_in_order_traversal(node_t p, list_t lis);
void nd_pre_order_traversal(node_t p, list_t lis);
unsigned char height(node_t p);
void nd_free(node_t p);


avl_tree_t tr_create(comparator(compare)){
	avl_tree_t tree = (avl_tree_t) malloc(sizeof(avl_tree_s));
	tree->compare = compare;
	tree->root = NULL;
	tree->min = NULL;
	tree->max = NULL;
	tree->size = 0;
	return tree;
}

// insert k key in a tree
boolean tr_insert(avl_tree_t tree, const void * k) {
	boolean inserted = false;
	tree->root = nd_insert(tree->root, k, tree->compare, &inserted);
	if(inserted) tree->size = tree->size +1;
	tree->min = nd_findmin(tree->root);
	tree->max = nd_findmax(tree->root);;
	return inserted;
}

boolean tr_insert_all(avl_tree_t tree, iterator_t it){
	void * e;
	boolean acum = false, r;
	while(it->hasNext(it)){
		e = it->next(it);
		r = tr_insert(tree, e);
		if(r) acum = true;
	}
	return acum;
}

boolean tr_contains(avl_tree_t tree, const void * k){
	return nd_find(tree->root,k,tree->compare) !=NULL;
}

// find the minimal key in a tree
void * tr_findmin(avl_tree_t tree) {
	return tree->min->key;
}

// find the max key in a tree
void * tr_findmax(avl_tree_t tree) {
	return tree->max->key;
}

int tr_height(avl_tree_t tree) {
	return height(tree->root);
}

int tr_size(avl_tree_t tree) {
	return tree->size;
}

boolean tr_isEmpty(avl_tree_t tree){
	return tr_size(tree) == 0;
}

// deleting k key from p tree
boolean tr_remove_key(avl_tree_t tree, const void * k){
	boolean removed = true;
	tree->root = nd_remove_key(tree->root, k, tree->compare,&removed);
	if(removed) tree->size = tree->size-1;
	tree->min = nd_findmin(tree->root);
	tree->max = nd_findmax(tree->root);;
	return removed;
}

list_t tr_in_order_traversal(avl_tree_t tree, list_t lis) {
	nd_in_order_traversal(tree->root,lis);
	return lis;
}

list_t tr_pre_order_traversal(avl_tree_t tree, list_t lis) {
	nd_in_order_traversal(tree->root,lis);
	return lis;
}

void tr_free(avl_tree_t tree){
	if(tree!=NULL){
		if(tree->root!=NULL) nd_free(tree->root);
		free(tree);
	}
	tree=NULL;
}

node_t nd_create(void * k) {
	node_t nt = (node_t) malloc(sizeof(node_s));
	nt->key = k;
	nt->left = 0;
	nt->right = 0;
	nt->height = 1;
	return nt;
}

unsigned char height(node_t p) {
    return p?p->height:0;
}

int bfactor(node_t p) {
    return height(p->right)-height(p->left);
}

void fixheight(node_t p) {
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

node_t rotateright(node_t p) {
    node_t q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node_t rotateleft(node_t q) {
    node_t p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node_t balance(node_t p)  { // balancing the p node
    fixheight(p);
    if( bfactor(p)==2 ) {
        if( bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p)==-2 ) {
        if( bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // balancing is not required
}

// find k key in a tree with p root or NULL if not found
node_t nd_find(node_t p, void * k, comparator(compare))  {
	node_t r;
	if( !p ) {
    	return p;
    }
    if( compare(k,p->key) < 0 )
        r = nd_find(p->left,k,compare);
    else if( compare(k,p->key) > 0 )
        r = nd_find(p->right,k,compare);
    else
    	r = p;
    return r;
}

// insert k key in a tree with p root
node_t nd_insert(node_t p, void * k, comparator(compare), boolean * inserted)  {
	if( !p ) {
    	* inserted = true;
    	return nd_create(k);
    }
    if( compare(k,p->key) < 0 )
        p->left = nd_insert(p->left,k,compare, inserted);
    else if( compare(k,p->key) > 0 )
        p->right = nd_insert(p->right,k,compare, inserted);
    // k == p->key do nothing
    return balance(p);
}

// find a node with minimal key in a p tree
node_t nd_findmin(node_t p)   {
    return p->left?nd_findmin(p->left):p;
}

node_t nd_findmax(node_t p)   { // find a node with maximal key in a p tree
    return p->right?nd_findmax(p->right):p;
}
// deleting a node with minimal key from a p tree
node_t nd_removemin(node_t p)  {
    if( p->left==0 )
        return p->right;
    p->left = nd_removemin(p->left);
    return balance(p);
}

node_t nd_removemax(node_t p)  { // deleting a node with maximal key from a p tree
    if( p->right==0 )
        return p->left;
    p->right = nd_removemax(p->right);
    return balance(p);
}

// deleting k key from p tree
node_t nd_remove_key(node_t p, void * k, comparator(compare), boolean * removed)  {
    if( !p ) return 0;
    if( compare(k, p->key) < 0 )
        p->left = nd_remove_key(p->left,k,compare,removed);
    else if( compare(k,p->key) > 0 )
        p->right = nd_remove_key(p->right,k,compare,removed);
    else   { //  k == p->key
    	*removed = true;
        node_t q = p->left;
        node_t r = p->right;
        free(p);  //repasar
        if( !r ) return q;
        node_t min = nd_findmin(r);
        min->right = nd_removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

void nd_in_order_traversal(node_t p, list_t lis) {
        if(p) {
                nd_in_order_traversal(p->left, lis);
                ls_add(lis,p->key);
                nd_in_order_traversal(p->right, lis);
        }
}

void nd_pre_order_traversal(node_t p, list_t lis) {
        if(p) {
        		ls_add(lis,p->key);
                nd_pre_order_traversal(p->left, lis);
                nd_pre_order_traversal(p->right, lis);
        }
}

void nd_free(node_t p) {
        if(p) {
                nd_free(p->left);
                nd_free(p->right);
                free(p);
        }
        p=0;
}


