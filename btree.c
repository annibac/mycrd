#include "btree.h"

int insert_node(t_node *btree, int key, int value) {
    t_node *current_checking_node;
    t_node *last_node;
    t_node *node;

    printf("Start insert data..\nKey : %d\nValue : %d\n",key, value);

    node = malloc(sizeof(t_node));
    if (node == NULL){
        printf("Could not malloc t_btree\n");
        return(NULL);
    }
    current_checking_node = malloc(sizeof(t_node));
    if (current_checking_node == NULL){
        printf("Could not malloc t_btree\n");
        return(NULL);
    }

    last_node = malloc(sizeof(t_node));
    if (last_node == NULL){
        printf("Could not malloc t_btree\n");
        return(NULL);
    }

    if (!btree->key) {
        btree->key = key;
        btree->value = value;
        btree->left = NULL;
        btree->right = NULL;

        printf("Btree key : %d\n", btree->key);
        printf("Current node key : %d\n", node->key);
        printf("Current node value : %d\n", node->value);
        printf("Current node left : %s\n", node->left);
        printf("Current node right : %s\n", node->right);
        printf("First node added, Return node->key : %d\n",node->key);
        return btree->key;
    }
    else {
        current_checking_node = btree;
        while (current_checking_node->key != NULL) {
            if (current_checking_node->key == node->key) {
                current_checking_node->value = value;
                free(node);
                printf("Edit value, Return current node->key :");
                printf("%d", current_checking_node->key);
                printf("\n");
                return current_checking_node->key;
            }
            printf("Current checking node : %d\n", current_checking_node->key);
            last_node = current_checking_node;
            printf("Current key value : %d\n", key);
            printf("Current node left : %s\n", current_checking_node->left);
            printf("Current node right : %s\n", current_checking_node->right);
            printf("Current checking node key : %d\n", current_checking_node->key);
            printf("Key : %d\n", key);
            printf("Try to assign new value..\n");
            current_checking_node = key > current_checking_node->key ? &current_checking_node->right : &current_checking_node->left;
            printf("Current checking node after ternaire : %s\n", current_checking_node->key);
        }
        printf("Exit while\n");
        printf("Last node key, value, left, right: %d, %d, %s, %s\n", last_node->key, last_node->value, last_node->left, last_node->right);

        node->key = key;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
        if (node->key > last_node->key) {
            last_node->right = malloc(sizeof(t_node*));
            if (last_node->right == NULL){
                printf("Could not malloc t_btree\n");
                return(NULL);
            }
            last_node->right = node;
        }
        else {
            last_node->left = malloc(sizeof(t_node*));
                if (last_node->left == NULL){
                    printf("Could not malloc t_btree\n");
                    return(NULL);
                }
            last_node->left = node;
            }
        printf("Insert new node, Return current node->key : %d\n", node->key);
        return node->key;
    }
}

int search_node(t_node *btree, int key) {
    t_node *current_checking_node;
    current_checking_node = btree;
    printf("Search for : %d", key);
    while (current_checking_node != NULL) {
        printf("Current checking key: %d\n", current_checking_node->key);
        if (current_checking_node->key == key){
                printf("\nResult value : %d\n", current_checking_node->value);
                return current_checking_node->value;
            }
        current_checking_node = key > current_checking_node->key ? current_checking_node->right : current_checking_node->left;
    }
    printf("-1\n");
    return (-1);
}

int delete_node(t_node *btree, int key) {

}

int main(int argc, char* argv) {
    t_node *btree;
    if ((btree = malloc(sizeof(t_node*))) == NULL){
        printf("Could not malloc t_btree\n");
        return(0);
    }
//    btree = NULL;
    btree->key = NULL;
    btree->value = NULL;
    btree->left = NULL;
    btree->right = NULL;

    insert_node(btree, 84, 84);
    printf("Current btree key : %d\n", btree->key);
    insert_node(btree, 9, 9);
    insert_node(btree, 9, 17);
    printf("Current btree key : %d\n", btree->left->key);
    insert_node(btree, 98, 98);
    printf("Current btree key : %d\n", btree->right->key);
    insert_node(btree, 23, 23);
    insert_node(btree, 79, 79);

    search_node(btree, 85);
    search_node(btree, 23);
    search_node(btree, 13);

//    delete_node(btree, 84, 2);

    return 1;
}