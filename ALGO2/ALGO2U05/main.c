#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


// definicie stromovych struktur
// AVL
typedef  struct AVL_node {
    int key;
    int height;
    struct AVL_node* parent;
    struct AVL_node* right;
    struct AVL_node* left;
} AVL_node;

typedef struct AVL_tree {
    AVL_node* root;
} AVL_tree;



// vytvorenie stromu
AVL_tree* avl_create() {
    AVL_tree* new_tree = malloc(sizeof(AVL_tree));
    new_tree->root = NULL;
    return new_tree;
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


// funkcie pre pracu s vyskou
int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int height(AVL_node* node) {
    if (node == NULL) {
        return -1;
    } else {
        return node->height;
    }
}

void updateHeight(AVL_node* node) {
    node->height = 1 + max(height(node->right), height(node->left));
}

// univerzalna funkcia na rotacie a abstrakcie rotateR a rotateL
enum Direction { LEFT, RIGHT };

AVL_node* rotate(AVL_node* root, enum Direction dir) {
    if (root == NULL) return NULL;
    AVL_node* child = NULL;

    // urcenie hlavneho potomka podla smeru rotacie
    if (dir == RIGHT) {
        child = root->left;
    } else {
        child = root->right;
    }

    // ak potomok neexistuje tak nieje mozna rotacia
    if (child == NULL) return root;

    // vymena potomka s rodicom
    child->parent = root->parent;
    if (root->parent != NULL) {
        if (root->parent->left == root) {
            root->parent->left = child;
        } else {
            root->parent->right = child;
        }
    }

    // rotacia
    if (dir == RIGHT) {
        // Pravá rotácia (ťaháme uzol doprava)
        root->left = child->right;
        if (child->right != NULL) {
            child->right->parent = root;
        }
        child->right = root;
    } else {
        // Ľavá rotácia (ťaháme uzol doľava)
        root->right = child->left;
        if (child->left != NULL) {
            child->left->parent = root;
        }
        child->left = root;
    }

    // nastavenie noveho rodica povodnemu rootu
    root->parent = child;

    // aktualizovanie vysky stromu
    updateHeight(root);
    updateHeight(child);


}

AVL_node* rotateR(AVL_node* root) {
    return rotate(root, RIGHT);
}

AVL_node* rotateL(AVL_node* root) {
   return rotate(root,LEFT);
}

// aktualizacia root prvku
void updateRoot(AVL_tree* tree) {
    AVL_node* node = tree->root;
    while (node->parent != NULL) {
        node = node->parent;
    }
    tree->root = node;
}

// ziskanie balance factoru
int getBalance(AVL_node* node) {
    return height(node->left) - height(node->right);
}
// pridavanie do AVL stromu
int avl_add(AVL_tree* tree, int key) {
    if (tree->root == NULL) {
        tree->root = avl_create_node(key,NULL);
        return 1;
    }
    AVL_node* root = tree->root;
    int avl_add_node(AVL_node* node,const int key);
    int success = avl_add_node(root, key);
    updateRoot(tree);
    return success;
}

int avl_add_node(AVL_node* node,const int key) {
    // pridanie prvku
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

    // uprava vysky
    updateHeight(node);

    // balancing
    int balance = getBalance(node);
    if (balance > 1) {
        if (getBalance(node->left) < 0) {
            rotateL(node->left);
        }
        rotateR(node);
    } if (balance < -1) {
        if (getBalance(node->right) > 0) {
            rotateR(node->right);
        }
        rotateL(node);
    }
    return success;
}


void print_tree(AVL_tree* root) {
    if (root == NULL) {
        printf("#\n");
        return;
    }
    AVL_node* node = root->root;
    void print_tree_help(AVL_node* root,int depth,char prefix);

    print_tree_help(node, 0, '>');
    printf("\n");
}

void print_tree_help(AVL_node* node, int depth,char prefix) {
    if (node->right != NULL) {
        print_tree_help(node->right, depth+1,'/');
    }
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    printf("%c%d h:%d\n",prefix, node->key,node->height);
    if (node->left != NULL) {
        print_tree_help(node->left, depth+1, '\\');
    }
}

// A TERAZ..... NASTAVA KAMEN URAZU.... avl_height()
// jk get shit on Simon :DD
int avl_height(AVL_tree* tree) {
    if (tree == NULL) {
        return -1;
    }
    return tree->root->height;
}

void main() {
    AVL_tree* testTree = avl_create();
    avl_add(testTree,1);
    avl_add(testTree,2);
    avl_add(testTree,3);
    avl_add(testTree,4);
    avl_add(testTree,5);
    avl_add(testTree,6);
    avl_add(testTree,7);
    avl_add(testTree,8);
    avl_add(testTree,9);
    avl_add(testTree,10);
;
    print_tree(testTree);
;
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


