#include <locale.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} node;

typedef struct List {
    struct Node *first;
} list;

int length(list seznam) {
    int length = 0;
    if (seznam.first == NULL) {
        return length;
    }
    node *curr = seznam.first;
    do {
        length++;
        curr = curr->next;
    } while (curr != NULL);
    return length;
}

void print_list(list seznam) {
    printf("[");
    node *curr = seznam.first;
    if (curr != NULL) { // Musíme ověřit, že seznam není úplně prázdný
        do {
            printf("%d", curr->data);
            if (curr->next != NULL) {
                printf(", ");
            }
            curr = curr->next;
        } while (curr != NULL);
        printf("]\n");
    }
}

void add_start(list *seznam, node *uzel) {
    uzel->next = seznam->first;
    seznam->first = uzel;
}

void add_end(list *seznam, node *uzel) {
    uzel->next = NULL;
    node *curr = seznam->first;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = uzel;
}

void add_position(list *seznam, node *uzel, int position) {
    if (length(*seznam) < position) {
        printf("position too big");
        return;
    } else if (position == 0) {
        add_start(seznam, uzel);
        printf("added to start");
        return;
    } else if (length(*seznam) == position) {
        add_end(seznam, uzel);
        printf("added to end");
        return;
    } else {
        int currLvl = 0;
        node *curr = seznam->first;
        if (currLvl == position-1) {

        }
        while (currLvl != position-1) {
            currLvl++;
            curr = curr->next;
        }
        uzel->next = curr->next;
        curr->next = uzel;
        return;
    }




}


int main() {
    node n0, n1, n2, n3, n4, n1_5;

    n0.data = 0;
    n4.data = 40;
    n1_5.data = 15;

    n1.data = 10;
    n2.data = 20;
    n3.data = 30;

    n1.next = &n2;
    n2.next = &n3;
    n3.next = NULL;

    list zoznam;
    zoznam.first = &n1;

    add_position(&zoznam, &n1, 1);
    add_end(&zoznam, &n4);
    add_start(&zoznam, &n0);
    int length1 = length(zoznam);
    printf("%d \n", length1);
    print_list(zoznam);
    return 0;
}