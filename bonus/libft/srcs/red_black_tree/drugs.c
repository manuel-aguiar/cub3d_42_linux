/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drugs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:55:41 by marvin            #+#    #+#             */
/*   Updated: 2024/02/06 17:55:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

https://epaperpress.com/sortsearch/txt/rbtr.txt


// reentrant red-black tree

#include <stdlib.h>
#include "rbtr.h"

typedef enum { BLACK, RED } NodeColor;

typedef struct NodeTag {
    struct NodeTag *left;       // left child
    struct NodeTag *right;      // right child
    struct NodeTag *parent;     // parent
    NodeColor color;            // node color (BLACK, RED)
    void *key;                  // key used for searching
    void *val;                // user data
} NodeType;

typedef struct RbtTag {
    NodeType *root;   // root of red-black tree
    NodeType sentinel;
    int (*compare)(void *a, void *b);    // compare keys
} RbtType;

// all leafs are sentinels
#define SENTINEL &rbt->sentinel

RbtHandle rbtNew(int(*rbtCompare)(void *a, void *b)) {
    RbtType *rbt;
    
    if ((rbt = (RbtType *)malloc(sizeof(RbtType))) == NULL) {
        return NULL;
    }

    rbt->compare = rbtCompare;
    rbt->root = SENTINEL;
    rbt->sentinel.left = SENTINEL;
    rbt->sentinel.right = SENTINEL;
    rbt->sentinel.parent = NULL;
    rbt->sentinel.color = BLACK;
    rbt->sentinel.key = NULL;
    rbt->sentinel.val = NULL;

    return rbt;
}

static void deleteTree(RbtHandle h, NodeType *p) {
    RbtType *rbt = h;

    // erase nodes depth-first
    if (p == SENTINEL) return;
    deleteTree(h, p->left);
    deleteTree(h, p->right);
    free(p);
}

void rbtDelete(RbtHandle h) {
    RbtType *rbt = h;

    deleteTree(h, rbt->root);
    free(rbt);
}

static void rotateLeft(RbtType *rbt, NodeType *x) {

    // rotate node x to left

    NodeType *y = x->right;

    // establish x->right link
    x->right = y->left;
    if (y->left != SENTINEL) y->left->parent = x;

    // establish y->parent link
    if (y != SENTINEL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    } else {
        rbt->root = y;
    }

    // link x and y
    y->left = x;
    if (x != SENTINEL) x->parent = y;
}

static void rotateRight(RbtType *rbt, NodeType *x) {

    // rotate node x to right

    NodeType *y = x->left;

    // establish x->left link
    x->left = y->right;
    if (y->right != SENTINEL) y->right->parent = x;

    // establish y->parent link
    if (y != SENTINEL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    } else {
        rbt->root = y;
    }

    // link x and y
    y->right = x;
    if (x != SENTINEL) x->parent = y;
}

static void insertFixup(RbtType *rbt, NodeType *x) {

    // maintain red-black tree balance after inserting node x

    // check red-black properties
    while (x != rbt->root && x->parent->color == RED) {
        // we have a violation
        if (x->parent == x->parent->parent->left) {
            NodeType *y = x->parent->parent->right;
            if (y->color == RED) {

                // uncle is RED
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {

                // uncle is BLACK
                if (x == x->parent->right) {
                    // make x a left child
                    x = x->parent;
                    rotateLeft(rbt, x);
                }

                // recolor and rotate
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateRight(rbt, x->parent->parent);
            }
        } else {

            // mirror image of above code
            NodeType *y = x->parent->parent->left;
            if (y->color == RED) {

                // uncle is RED
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {

                // uncle is BLACK
                if (x == x->parent->left) {
                    x = x->parent;
                    rotateRight(rbt, x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateLeft(rbt, x->parent->parent);
            }
        }
    }
    rbt->root->color = BLACK;
}

RbtStatus rbtInsert(RbtHandle h, void *key, void *val) {
    NodeType *current, *parent, *x;
    RbtType *rbt = h;

    // allocate node for data and insert in tree

    // find future parent
    current = rbt->root;
    parent = 0;
    while (current != SENTINEL) {
        int rc = rbt->compare(key, current->key);
        if (rc == 0)
            return RBT_STATUS_DUPLICATE_KEY;
        parent = current;
        current = (rc < 0) ? current->left : current->right;
    }

    // setup new node
    if ((x = malloc (sizeof(*x))) == 0)
        return RBT_STATUS_MEM_EXHAUSTED;
    x->parent = parent;
    x->left = SENTINEL;
    x->right = SENTINEL;
    x->color = RED;
    x->key = key;
    x->val = val;

    // insert node in tree
    if(parent) {
        if(rbt->compare(key, parent->key) < 0)
            parent->left = x;
        else
            parent->right = x;
    } else {
        rbt->root = x;
    }

    insertFixup(rbt, x);

    return RBT_STATUS_OK;
}

void deleteFixup(RbtType *rbt, NodeType *x) {

    // maintain red-black tree balance after deleting node x

    while (x != rbt->root && x->color == BLACK) {
        if (x == x->parent->left) {
            NodeType *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft (rbt, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotateRight (rbt, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotateLeft (rbt, x->parent);
                x = rbt->root;
            }
        } else {
            NodeType *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight (rbt, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft (rbt, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotateRight (rbt, x->parent);
                x = rbt->root;
            }
        }
    }
    x->color = BLACK;
}

RbtStatus rbtErase(RbtHandle h, RbtIterator i) {
    NodeType *x, *y;
    RbtType *rbt = h;
    NodeType *z = i;

    if (z->left == SENTINEL || z->right == SENTINEL) {
        // y has a SENTINEL node as a child
        y = z;
    } else {
        // find tree successor with a SENTINEL node as a child
        y = z->right;
        while (y->left != SENTINEL) y = y->left;
    }

    // x is y's only child
    if (y->left != SENTINEL)
        x = y->left;
    else
        x = y->right;

    // remove y from the parent chain
    x->parent = y->parent;
    if (y->parent)
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    else
        rbt->root = x;

    if (y != z) {
        z->key = y->key;
        z->val = y->val;
    }


    if (y->color == BLACK)
        deleteFixup (rbt, x);

    free (y);

    return RBT_STATUS_OK;
}

RbtIterator rbtNext(RbtHandle h, RbtIterator it) {
    RbtType *rbt = h;
    NodeType *i = it;

    if (i->right != SENTINEL) {
        // go right 1, then left to the end
        for (i = i->right; i->left != SENTINEL; i = i->left);
    } else {
        // while you're the right child, chain up parent link
        NodeType *p = i->parent;
        while (p && i == p->right) {
            i = p;
            p = p->parent;
        }

        // return the "inorder" node
        i = p;
    }
    return i != SENTINEL ? i : NULL;
}

RbtIterator rbtBegin(RbtHandle h) {
    RbtType *rbt = h;

    // return pointer to first value
    NodeType *i;
    for (i = rbt->root; i->left != SENTINEL; i = i->left);
    return i != SENTINEL ? i : NULL;
}

RbtIterator rbtEnd(RbtHandle h) {
   // return pointer to one past last value
   return NULL;
}

void rbtKeyValue(RbtHandle h, RbtIterator it, void **key, void **val) {
    NodeType *i = it;

    *key = i->key;
    *val = i->val;
}


void *rbtFind(RbtHandle h, void *key) {
    RbtType *rbt = h;

    NodeType *current;
    current = rbt->root;
    while(current != SENTINEL) {
        int rc = rbt->compare(key, current->key);
        if (rc == 0) return current;
        current = (rc < 0) ? current->left : current->right;
    }
    return NULL;
}

*/