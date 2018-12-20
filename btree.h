#include <stdlib.h>
#include <stdio.h>


typedef struct s_node {
    int key;
    int value;
    struct s_node *left;
    struct s_node *right;
} t_node;
