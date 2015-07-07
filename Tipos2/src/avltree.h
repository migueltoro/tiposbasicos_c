/*
 * avltree.h
 *
 *  Created on: May 5, 2015
 *      Author: Boss
 */

#ifndef SRC_AVLTREE_H_
#define SRC_AVLTREE_H_

#include "tipos.h"
#include "list.h"
#include "iterator.h"

union data {
	int i;
	void * k;
};

typedef struct node {
    void * key;
    unsigned char height;
    struct node * left;
    struct node * right;
} node_s;

typedef node_s * node_t;

typedef struct {
	int size;
	node_t min;
	node_t max;
	node_t root;
	comparator(compare);
}avl_tree_s;

typedef avl_tree_s * avl_tree_t;


avl_tree_t tr_create(comparator(c));
// insert k key in a tree
boolean tr_insert(avl_tree_t tree, const void * k);
// insert all keys in iterator in a tree
boolean tr_insert_all(avl_tree_t tree, iterator_t it);
// true if k key is in a tree
boolean tr_contains(avl_tree_t tree,const void * k);
// find the minimal key in a tree
void * tr_findmin(avl_tree_t tree);
// find the maximal key in a tree
void * tr_findmax(avl_tree_t tree);
// deleting a key from a tree
boolean tr_remove_key(avl_tree_t tree, const void * k);
// height of a tree
int tr_height(avl_tree_t tree);
int tr_size(avl_tree_t tree);
boolean tr_isEmpty(avl_tree_t tree);
list_t tr_in_order_traversal(avl_tree_t tree, list_t lis);
list_t tr_pre_order_traversal(avl_tree_t tree, list_t lis);
void tr_free(avl_tree_t tree);

#endif /* SRC_AVLTREE_H_ */
