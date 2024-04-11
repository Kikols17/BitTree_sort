#include <stdio.h>

#ifndef BITTREESORT_H
#define BITTREESORT_H


typedef struct Node {
    int count;      // start with -1 if not leaf, with 0 if leaf
    int val;        // start with -1 if not leaf, with real val if leaf
    struct Node *zero;
    struct Node *one;
} Node;


Node *createNode(int init_count, int init_val);
void destroyNode(Node *node);

Node *movedown(struct Node *node, int side, int init_count, int init_val);
int incrval(struct Node *root, int val);
int fetchorderly(struct Node *node, int side, int index, int *array);


#endif