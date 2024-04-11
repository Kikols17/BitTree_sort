#include <stdio.h>
#include <stdlib.h>

#include "BitTree_sort.h"

#ifndef BITTREESORT_C
#define BITTREESORT_C

Node *createNode(int init_count, int init_val) {
    struct Node *node = malloc( sizeof(struct Node) );
    if (node==NULL) {
        // malloc failed, get more ram at "https://downloadmoreram.com/"
        return NULL;
    }
    node->count = init_count;
    node->val = init_val;
    node->zero = NULL;
    node->one = NULL;
    //printf("node created\n");
    return node;
}

void destroyNode(Node *node) {
    if (node->zero!=NULL) {
        destroyNode(node->zero);
    }
    if (node->one!=NULL) {
        destroyNode(node->one);
    }
    free(node);
}

Node *movedown(struct Node *node, int side, int init_count, int init_val) {
    /* Moves to descendent of node (to zero, if side==0; to 1 if side==1)
     * 
     * If descendent does not exist, create it.
     * Return pointer to descendent.
     */
    struct Node *new_node;
    if (side==0) {
        if (node->zero==NULL) {
            new_node = createNode(init_count, init_val);
            node->zero = new_node;
        }
        return node->zero;
    } else {
        if (node->one==NULL) {
            new_node = createNode(init_count, init_val);
            node->one = new_node;
        }
        return node->one;
    }
    return NULL;    // ????
}


int incrval(struct Node *node, int val) {
    /* Used to increvent count of a given val
     * 
     * if branches down to val do not exist, create them, making non leaf nodes' count = -1, and leaf node's count = 0
     * if branches down to val does exist, add +1 to leaf node's count
     * 
     */

    for (int i=(int)sizeof(int)*8-1; i>0; --i) {
        // for every bit in type (except last bit, that will be leaf)
        if ( (((val) >> (i)) & 1)==0 ) {
            node = movedown(node, 0, -1, -1);
            //printf("0");
        } else {
            node = movedown(node, 1, -1, -1);
            //printf("1");
        }
        if (node==NULL) {
            // create node failed
            return -1;
        }
    }

    // last bit should be last node which should be leaf
    if ( (((val) >> (0)) & 1)==0 ) {
        node = movedown(node, 0, 0, val);
        node->count++;
        //printf("0");
    } else {
        node = movedown(node, 1, 0, val);
        node->count++;
        //printf("1");
    }
    if (node==NULL) {
        // create node failed
        return -1;
    }
    //printf("\n");

    return 0;
}



int fetchorderly(struct Node *node, int side, int index, int *array) {
    if (node==NULL) {
        return index;
    }

    if (node->count!=-1) {
        //printf("%d ", node->val);
        array[index] = node->val;
        return index+1;
    }

    if (side==0) {
        index = fetchorderly(node->zero, side, index, array);
        index = fetchorderly(node->one, side, index, array);
    } else {
        index = fetchorderly(node->one, side, index, array);
        index = fetchorderly(node->zero, side, index, array);
    }
    return index;
}


int bittreesort(int n, int *array) {
    /* Sorts array
     *
     *  INPUT:
     *      int n: number of elements of the array
     *      int *array: pointer to the array that is to be sorted 
     */
    struct Node *root = createNode(-1, -1);

    for (int i=0; i<n; ++i) {
        if ( incrval(root, array[i])==-1 ) {
            // incrval failed because createNode failed
            destroyNode(root);
            return -1;
        }
    }

    int index = 0;
    index = fetchorderly(root->one, 0, index, array);
    index = fetchorderly(root->zero, 0, index, array);

    destroyNode(root);

    return 0;
}

#endif