#include "bintree.h"
#include "dlinkedlist.h"

#include <stdio.h>
#include <stdlib.h>

BinTree* read_tree(FILE* f);

// calculate the height of a BinTree given a specific
// BinTreeNode (e.g. root)
// This method should technically be in bintree.c
int get_height(BinTreeNode* btn) {
    if (btn == NULL)
        return 0;
    else {
        // get the largest subtree recurisvely
        int lh = get_height(btn->left);
        int rh = get_height(btn->right);

        return (lh > rh ? lh : rh) + 1;
    }
}

void print_tree_level(BinTreeNode* btn, int level, FILE* f) {
    if (btn == NULL) {
        return;
    }

    if (level == 0) {
        fprintf(stdout, "%d\n", btn->key);
    }
    else if (level > 0) {
        print_tree_level(btn->left, level-1, f);
        print_tree_level(btn->right, level-1, f);
    }
}

int main(void) {
    BinTree* t = read_tree(stdin);
    if(!t) {
        fprintf(stderr, "Fehler beim Lesen der Eingabe.\n");
        return 1;
    }

    // This method has NOT the best worst-case-runtime, since it
    // does not use any other data structure
    // Instead it iterates over the entire multiple times,
    // which is rather slow ...
    int height = get_height(t->root);
    for (int i = 0; i < height; i++) {
        print_tree_level(t->root, i, stdout);
    }


    /* TODO Geben Sie t ebenenweise aus.
     *
     * Genauer:
     *
     * - Geben Sie zunächst alle Knoten auf Ebene 0 aus (das ist nur die Wurzel)
     * - Geben Sie dann alle Knoten auf Ebene 1 aus (die Kinder der Wurzel)
     * - Geben Sie dann alle Knoten auf Ebene 2 aus
     *
     * ...usw...
     *
     * - Die Ebenen sollen jeweils von links nach rechts ausgegeben werden, mit
     * einem Knoten pro Zeile (s. Beispiel auf dem Übungsblatt)
     *
     * Sie dürfen zur Lösung alle Datenstrukturen aus dem Repository verwenden.
     * Wählen Sie einen Datenstruktur, die zu einer optimalen asymptotischen
     * Worst-Case-Laufzeit führt und passen Sie die Datenstruktur ggf. an Ihre
     * Bedürfnisse an.
     *
     * Passen Sie ggf. das Makefile an!
     *
     * Markieren Sie außerdem in Frage.md, welche Datenstruktur Sie als
     * Grundlage gewählt haben.
     */

    bt_destroy(t);
    free(t);

    return 0;
}

BinTree* read_tree(FILE* f) {
    BinTree* t = create_bintree();

    while(!feof(f)) {
        int key;

        if(fscanf(f, "%d\n", &key) != 1) {
            fprintf(stderr, "Fehlerhafte Zeile.\n");
            bt_destroy(t);
            free(t);
            return NULL;
        }

        bt_add(t, key);
    }



    return t;
}
