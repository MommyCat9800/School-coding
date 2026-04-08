#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef  struct node {
    int key;
    int height;
    struct node* parent;
    struct node* right;
    struct node* left;
} AVL_node;

typedef struct AVL_tree {
    AVL_node* root;
} AVL_tree;

AVL_tree* avl_create() {
    AVL_tree* new_tree = malloc(sizeof(AVL_tree));
    new_tree->root = NULL;
    return new_tree;
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

void updateHeight(AVL_node* node) {
    if (node->left == NULL && node->right != NULL) node->height = 1 + node->right->height;
    else if (node->right == NULL && node->left != NULL) node->height = 1 + node->left->height;
    else if (node->right == NULL && node->left == NULL) node->height = 0;
    else node->height = 1 + max(node->right->height, node->left->height);
}

AVL_node* avl_create_node(int key, AVL_node* parent) {
    AVL_node* new_node = malloc(sizeof(AVL_node));
    new_node->key = key;
    new_node->height = 0;

    new_node->parent = parent;
    new_node->right = NULL;
    new_node->left = NULL;
    return new_node;
}

int avl_add_node(AVL_node* node, int key) {
    int success;
    if (key < node->key) {
        if (node->left == NULL) {
            success = 1;
            node->left = avl_create_node(key,node);
        } else {
            success = avl_add_node(node->left, key);
        }
    } else if (key > node->key) {
        if (node->right == NULL) {
            success = 1;
            node->right = avl_create_node(key, node);
        } else {
            success = avl_add_node(node->right, key);
        }
    } else {
        success = 0;
    }
    updateHeight(node);

    return success;
}

int avl_add(AVL_tree* tree, int key) {
    if (tree->root == NULL) {
        tree->root = avl_create_node(key,NULL);
        return 1;
    }
    return avl_add_node(tree->root, key);

}






// old

// typedef  struct n {
//     int key;
//     struct n* parent;
//     struct n* right;
//     struct n* left;
// } BST;
//
// AVL_node* createTree(int const key, AVL_node* parent) {
//     AVL_node* new_node = (AVL_node*)malloc(sizeof(AVL_node));
//     new_node->key = key;
//     new_node->height = 0;
//     new_node->parent = parent;
//     new_node->left = NULL;
//     new_node->right = NULL;
//     return new_node;
// }
//
//
// void add(AVL_node* root, int key) {
//     if (key < root->key) {
//         if (root->left == NULL) {
//             root->left = createTree(key, root);
//         } else {
//             add(root->left, key);
//         }
//     } else {
//         if (root->right == NULL) {
//             root->right = createTree(key, root);
//         } else {
//             add(root->right, key);
//         }
//     }
//
// }
//
// // ReSharper disable once CppParameterMayBeConst
// BST* arrToTree(int arr[], int len) {
//     BST* newTree = createTree(arr[0], NULL);
//     for (int i = 1; i < len; i++) {
//         add(newTree, arr[i]);
//     }
//     return newTree;
// }
//
// BST* search_tree(BST* root,const int key) {
//     if (root->key == key) {
//         return root;
//     }
//     if (root->key > key) {
//         if (root->left == NULL) {
//             return NULL;
//         }
//         return search_tree(root->left, key);
//     }
//     // if (root->key < key)
//     {
//         if (root->right == NULL) {
//             return NULL;
//         }
//         return search_tree(root->right, key);
//     }
// }
//
// void print_tree(BST* root) {
//     // ReSharper disable once CppDeclarationHidesLocal
//     if (root == NULL) {
//         printf("#\n");
//         return;
//     }
//
//     void print_tree_help(BST* root,int depth,char prefix);
//
//     print_tree_help(root, 0, '>');
//     printf("\n");
// }
//
// void print_tree_help(BST* root, int depth,char prefix) {
//     if (root->right != NULL) {
//         print_tree_help(root->right, depth+1,'/');
//     }
//     for (int i = 0; i < depth; i++) {
//         printf("    ");
//     }
//     printf("%c%d\n",prefix, root->key);
//     if (root->left != NULL) {
//         print_tree_help(root->left, depth+1, '\\');
//     }
// }
//
// int tree_height(BST* root) {
//     int left_height, right_height;
//     if (root == NULL) {
//         return -1;
//     }
//     left_height = 1 + tree_height(root->left);
//     right_height = 1 + tree_height(root->right);
//
//     if (left_height >= right_height) {
//         return left_height;
//     } else {
//         return right_height;
//     }
// }
//
// int tree_elem_count(BST* root) {
//     if (root != NULL) {
//         return tree_elem_count(root->left) + tree_elem_count(root->right) + 1;
//     } else {
//         return 0;
//     }
// }
//
// void in_order(const BST* root, int arr[]) {
//     arr = (int*)malloc(sizeof(int)*tree_elem_count(root));
//     void in_order_help(const BST* root,int index, int arr[]);
//     int index = 0;
//     in_order_help(root,index,arr);
// }
//
// void in_order_help(const BST* root,int index,int arr[]) {
//     // TODO finish later
// }
//
// BST* findMin(BST* root) {
//     if (root->left == NULL) {return root;}
//     else {return findMin(root->left);}
// }
//
// BST* remNode(BST* root, int key) {
//     if (root == NULL) {return NULL;}
//     if (key < root->key) {
//         root->left = remNode(root->left, key);
//     } else if (key > root->key) {
//         root->right = remNode(root->right, key);
//     } else {
//         if (root->left == NULL) {
//             BST* tempNode = root->right;
//             if (tempNode != NULL) {tempNode->parent = root->parent;}
//             free(root);
//             return tempNode;
//         }
//         if (root->right == NULL) {
//             BST* tempNode = root->left;
//             if (tempNode != NULL) {tempNode->parent = root->parent;}
//             free(root);
//             return tempNode;
//         }
//
//         BST* successor = findMin(root->right);
//         root->key = successor->key;
//         root->right = remNode(root->right, successor->key);
//     }
//     return root;
// }
//
// BST* rotateR(BST* root) {
//     if (root == NULL || root->left == NULL) return root;
//
//     BST* newRoot = root->left;
//     // zmena rodica
//     newRoot->parent = root->parent;
//     root->parent = newRoot;
//     // zmena naslednika u rodica
//     if (newRoot->parent != NULL) {
//         if (newRoot->parent->left == root) {
//             newRoot->parent->left = newRoot;
//         } else {
//             newRoot->parent->right = newRoot;
//         }
//     }
//     //  vymena podstromu B
//     root->left = newRoot->right;
//     if (root->left != NULL) {
//         root->left->parent = root;
//     }
//     newRoot->right = root;
//
//     while (newRoot->parent != NULL) {
//         newRoot = newRoot->parent;
//     }
//     return newRoot;
// }
//
// BST* rotateL(BST* root) {
//     if (root == NULL || root->right == NULL) return root;
//
//     BST* newRoot = root->right;
//     // zmena rodica
//     newRoot->parent = root->parent;
//     root->parent = newRoot;
//     // zmena naslednika u rodica
//     if (newRoot->parent != NULL) {
//         if (newRoot->parent->right == root) {
//             newRoot->parent->right = newRoot;
//         } else {
//             newRoot->parent->left = newRoot;
//         }
//     }
//     //  vymena podstromu B
//     root->right = newRoot->left;
//     if (root->right != NULL) {
//         root->right->parent = root;
//     }
//     newRoot->left = root;
//
//     while (newRoot->parent != NULL) {
//         newRoot = newRoot->parent;
//     }
//     return newRoot;
// }

void main() {
    // // vyska stromu
    //
    // int arr[] = {9,7,11,6,10,8,12};
    // Tree* my_tree = arrToTree(arr,7);
    // print_tree(my_tree);
    // printf("vyska stromu: %d\n",tree_height(my_tree));
    // printf("podstrom elementu 11 a jeho vyska: %d\n", tree_height(search_tree(my_tree, 11)));
    // print_tree(search_tree(my_tree, 11));
    // printf("podstrom elementu 12 a jeho vyska: %d\n", tree_height(search_tree(my_tree, 12)));
    // print_tree(search_tree(my_tree, 12));
    // printf("podstrom elementu 12->right a jeho vyska: %d\n", tree_height(search_tree(my_tree, 12)->right));
    // print_tree(search_tree(my_tree, 12)->right);


    // // mazanie
    //
    // int arr[] = {9,7,11,6,10,8,12};
    // Tree* my_tree = arrToTree(arr ,7);
    // printf("Vypis stromu: \n");
    // print_tree(my_tree);
    //
    // printf("Vymaz zo stromu 11:\n");
    // remNode(my_tree, 11);
    // print_tree(my_tree);

    // // Rotacie
    //
    // int arr[] = {4,2,6,3,5,1,7,8};
    // Tree* newTree = arrToTree(arr, 8);
    // printf("Vypis stromu: \n");
    // print_tree(newTree);
    // printf("Rotovany strom R:\n");
    // newTree = rotateR(search_tree(newTree,4));
    // print_tree(newTree);
    // printf("Rotovany strom L:\n");
    // newTree = rotateL(search_tree(newTree,2));
    // print_tree(newTree);
}

