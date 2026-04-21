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

// BST
typedef  struct BST_node {
int key;
struct BST_node* parent;
struct BST_node* right;
struct BST_node* left;
} BST_node;

typedef struct BST_tree {
    BST_node* root;
} BST_tree;






// AVL časť

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

int get_height(AVL_node* node) {
    if (node == NULL) {
        return -1;
    } else {
        return node->height;
    }
}

void updateHeight(AVL_node* node) {
    node->height = 1 + max(get_height(node->right), get_height(node->left));
}

// univerzalna funkcia na rotacie a abstrakcie rotateR a rotateL
enum Direction { LEFT, RIGHT };

AVL_node* avl_rotate(AVL_node* root, enum Direction dir) {
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

AVL_node* avl_rotateR(AVL_node* root) {
    return avl_rotate(root, RIGHT);
}

AVL_node* avl_rotateL(AVL_node* root) {
   return avl_rotate(root,LEFT);
}

// aktualizacia root prvku
void updateRoot(AVL_tree* tree) {
    AVL_node* node = tree->root;
    while (node->parent != NULL) {
        node = node->parent;
    }
    tree->root = node;
}

// ziskanie balance faktoru
int getBalance(AVL_node* node) {
    return get_height(node->left) - get_height(node->right);
}

// rebalancing
void rebalance(AVL_node* node) {
    int balance = getBalance(node);
    if (balance > 1) {
        if (getBalance(node->left) < 0) {
            avl_rotateL(node->left);
        }
        avl_rotateR(node);
    } if (balance < -1) {
        if (getBalance(node->right) > 0) {
            avl_rotateR(node->right);
        }
        avl_rotateL(node);
    }
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
    rebalance(node);
    return success;
}


// hladanie v AVL strome
int avl_search_node(AVL_node* root,const int key) {
    if (root->key == key) {
        return 1;
    }
    if (root->key > key) {
        if (root->left == NULL) {
            return 0;
        }
        return avl_search_node(root->left, key);
    }
    else {
        if (root->right == NULL) {
            return 0;
        }
        return avl_search_node(root->right, key);
    }
}

int avl_search(AVL_tree* tree, int key) {
    if (tree->root == NULL) {
        return 0;
    }
    return avl_search_node(tree->root, key);
}

// vypis stromu do konzoly (je to podstate in order akurat ze prvy sa vypisuje lavy potomok potom momentalny uzol a potom pravy potomok)
// nevedel som najst ako sa to vola, ale viem vdaka tomu spravit pekny vypis stromu otoceneho o 90 stupnov
void avl_print_tree_help(AVL_node* node, int depth,char prefix) {
    if (node->right != NULL) {
        avl_print_tree_help(node->right, depth+1,'/');
    }
    for (int i = 0; i < depth; i++) {
        printf("      ");
    }
    printf("%c%d (%d)\n",prefix, node->key,node->height);
    if (node->left != NULL) {
        avl_print_tree_help(node->left, depth+1, '\\');
    }
}

void avl_print_tree(AVL_tree* root) {
    if (root == NULL) {
        printf("#\n");
        return;
    }
    AVL_node* node = root->root;

    avl_print_tree_help(node, 0, '>');
    printf("\n");
}

int avl_delete_smallest(AVL_node* node) {
    int smallest;
    if (node->left != NULL) {
        smallest = avl_delete_smallest(node->left);
        updateHeight(node);
        rebalance(node);
    } else {
        if (node->parent->left == node) {
            if (node->right != NULL) {
                node->right->parent = node->parent;
                node->parent->left = node->right;
            } else {
                node->parent->left = NULL;
            }
        } else {
            if (node->right != NULL) {
                node->right->parent = node->parent;
                node->parent->right = node->right;
            } else {
                node->parent->right = NULL;
            }
        }

        smallest = node->key;
        free(node);
    }
    return smallest;
}

int avl_delete_node(AVL_node* node, int key) {
    int deleted;
    if (node->key > key) {
        // hladany prvok by mal byt v lavo
        if (node->left != NULL) {
            deleted = avl_delete_node(node->left, key);
        } else {
            // nieje tam nic
            deleted = 0;
        }
    } else if (node->key < key) {
        // hladany prvok by mal byt vpravo
        if (node->right != NULL) {
            deleted = avl_delete_node(node->right, key);
        }  else {
            // nieje tam nic
            deleted = 0;
        }
    } else {
        if (node->right != NULL && node->left != NULL) {
            // ma oboch potomkov
            node->key = avl_delete_smallest(node->right);
        } else if (node->right != NULL) {
            // ma praveho potomka
            AVL_node* child = node->right;
            node->key = child->key;
            node->left = child->left;
            node->right = child->right;

            // kontrola potomkov po zmene
            if (node->left != NULL) {
                node->left->parent = node;
            }
            if (node->right != NULL) {
                node->right->parent = node;
            }
            free(child);
        } else if (node->left != NULL) {
            // ma laveho potomka
            AVL_node* child = node->left;
            node->key = child->key;
            node->left = child->left;
            node->right = child->right;

            // kontrola potomkov po zmene
            if (node->left != NULL) {
                node->left->parent = node;
            }
            if (node->right != NULL) {
                node->right->parent = node;
            }
            free(child);
        } else {
            // je list
            // na ktorej strane rodica sa nachadza od rodica
            if (node->parent->left == node) {
                // je rodicov lavy potomok
                node->parent->left = NULL;
            } else {
                // je rodicov pravy potomok
                node->parent->right = NULL;
            }
            free(node);
            return 1;
        }

        deleted = 1;
    }
    // oprava vysky
    updateHeight(node);

    // balancing
    rebalance(node);
    return deleted;
}

int avl_delete(AVL_tree* tree, int key) {
    if (tree->root == NULL) {
        return 0;
    }
    int height = tree->root->height;
    int deleted = avl_delete_node(tree->root,key);

    if (deleted == 1 && height == 0) {
        tree->root = NULL;
    } else {
        updateRoot(tree);
    }

    return deleted;
}



int avl_height(AVL_tree* tree) {
    if (tree == NULL) {
        return -1;
    }
    return tree->root->height;
}





// ########################################################################################
// BST časť


// vypocet vysky
int bst_height_node(BST_node* root) {
    int left_height, right_height;
    if (root == NULL) {
        return -1;
    }
    left_height = 1 + bst_height_node(root->left);
    right_height = 1 + bst_height_node(root->right);

    if (left_height >= right_height) {
        return left_height;
    } else {
        return right_height;
    }
}

int bst_height(BST_tree* tree) {
    if (tree == NULL) {
        return -1;
    }
    return bst_height_node(tree->root);
}

// vytvorenie stromu
BST_tree* bst_create() {
    BST_tree* new_tree = malloc(sizeof(BST_tree));
    new_tree->root = NULL;
    return new_tree;
}

BST_node* bst_create_node(int key, BST_node* parent) {
    BST_node* new_node = malloc(sizeof(BST_node));
    new_node->key = key;

    new_node->parent = parent;
    new_node->right = NULL;
    new_node->left = NULL;
    return new_node;
}

// pridavanie do BST stromu
int bst_add(BST_tree* tree, int key) {
    if (tree->root == NULL) {
        tree->root = bst_create_node(key,NULL);
        return 1;
    }
    BST_node* root = tree->root;
    int bst_add_node(BST_node* node,const int key);
    int success = bst_add_node(root, key);
    return success;
}

int bst_add_node(BST_node* node,const int key) {
    // pridanie prvku
    int success;
    if (key < node->key) {
        if (node->left == NULL) {
            success = 1;
            node->left = bst_create_node(key,node);
        } else {
            success = bst_add_node(node->left, key);
        }
    } else if (key > node->key) {
        if (node->right == NULL) {
            success = 1;
            node->right = bst_create_node(key, node);
        } else {
            success = bst_add_node(node->right, key);
        }
    } else {
        success = 0;
    }
    return success;
}

// hladanie v bst strome
int bst_search_node(BST_node* root,const int key) {
    if (root->key == key) {
        return 1;
    }
    if (root->key > key) {
        if (root->left == NULL) {
            return 0;
        }
        return bst_search_node(root->left, key);
    }
    else {
        if (root->right == NULL) {
            return 0;
        }
        return bst_search_node(root->right, key);
    }
}

int bst_search(BST_tree* tree, int key) {
    if (tree->root == NULL) {
        return 0;
    }
    return bst_search_node(tree->root, key);
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
    avl_add(testTree,11);
    avl_add(testTree,12);
    avl_add(testTree,13);
    avl_add(testTree,14);
    avl_add(testTree,15);
    avl_add(testTree,16);
    avl_add(testTree,17);
    avl_add(testTree,18);
    avl_add(testTree,19);
    avl_add(testTree,20);

    avl_print_tree(testTree);

    printf("vyska stromu: %d\n",avl_height(testTree));
}

