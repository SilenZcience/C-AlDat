#ifndef CA_BINTREE_H_
#define CA_BINTREE_H_

/*  Diese Datei bitte nicht veraendern */

#include <stdio.h>
#include <stddef.h>

typedef struct BinTree BinTree;
typedef struct BinTreeNode BinTreeNode;

struct BinTreeNode {
    int key;
    BinTreeNode* left;
    BinTreeNode* right;
};

void bt_node_init(BinTreeNode* node, int key);
void bt_node_destroy(BinTreeNode* node);
BinTreeNode* create_bt_node(int key);

/* Binärer Suchbaum. Stellt sicher, dass jeder Schlüssel nur einmal
 * enthalten is */
struct BinTree {
  BinTreeNode* root;
  size_t size;
};

void bt_init(BinTree* t);
void bt_destroy(BinTree* bt);
BinTree* create_bintree();

// Liefert die Anzahl an Schlüsseln im Binärbaum zurück
size_t bt_size(BinTree* bt);

// Liefert Knoten mit Schlüssel key zurück oder NULL
BinTreeNode* bt_find(BinTree* bt, int key);

// Liefert einen Zeiger auf den Zeiger im Baum zurück,
// der auf den Knoten mit Schlüssel key zeigt.
BinTreeNode** bt_find_link(BinTree* bt, int key);

void bt_remove(BinTree* bt, int key);

// Entfernt den Knoten, auf den *link zeigt.
void bt_remove_link(BinTree* bt, BinTreeNode** link);

// Fügt key ein oder tut nichts, wenn key bereits vorhanden ist.
// Liefert in jedem Fall einen Knoten mit Schlüssel key zurück.
BinTreeNode* bt_add(BinTree* bt, int key);

void bt_print_preorder(BinTree* bt, FILE* f);
void bt_print_inorder(BinTree* bt, FILE* f);
void bt_print_postorder(BinTree* bt, FILE* f);

// Gibt Baum im DOT-Format aus
void bt_print_as_dot(BinTree* bt, FILE* f);

// TODO Implementieren Sie diese Methode, s. bintree.c
int bt_minimum(BinTree* bt);

// TODO Implementieren Sie diese Methode, s. bintree.c
int bt_maximum(BinTree* bt);
#endif
