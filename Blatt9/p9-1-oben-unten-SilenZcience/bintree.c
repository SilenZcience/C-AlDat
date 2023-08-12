#include "bintree.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

BinTreeNode** _pred(BinTreeNode* v);
void _bt_destroy(BinTreeNode* v);

BinTreeNode* bt_add_non_rec(BinTree* bt, int key);
BinTreeNode* _bt_add_rec(BinTree* bt, BinTreeNode* v, int key);
BinTreeNode* bt_add_rec(BinTree* bt, int key);
BinTreeNode* _bt_add_rec2(BinTree* bt, BinTreeNode** link, int key);
BinTreeNode* bt_add_rec2(BinTree* bt, int key);

void _bt_print_preorder(BinTreeNode* v, FILE* f);
void _bt_print_inorder(BinTreeNode* v, FILE* f);
void _bt_print_postorder(BinTreeNode* v, FILE* f);

void _bt_print_as_dot_rec(BinTreeNode* v, FILE* f);

void bt_node_init(BinTreeNode* node, int key) {
    node->key = key;
    node->left = NULL;
    node->right = NULL;
}

void bt_node_destroy(BinTreeNode* node) {
    // nichts zu tun
}

BinTreeNode* create_bt_node(int key) {
    BinTreeNode* node = malloc(sizeof(BinTreeNode));
    bt_node_init(node, key);
    return node;
}

void bt_init(BinTree* t) {
    t->root = NULL;
    t->size = 0;
}

BinTree* create_bintree() {
    BinTree* bt = malloc(sizeof(BinTree));
    bt_init(bt);
    return bt;
}

void bt_destroy(BinTree* bt) {
    _bt_destroy(bt->root);
    bt->root = NULL;
    bt->size = 0;
}

void _bt_destroy(BinTreeNode* v) {
    if(v == NULL) return;

    _bt_destroy(v->left);
    _bt_destroy(v->right);
    bt_node_destroy(v);
    free(v);
}

size_t bt_size(BinTree* bt) {
    return bt->size;
}

BinTreeNode* bt_add(BinTree* bt, int key) {
    return bt_add_non_rec(bt, key);
}

BinTreeNode* bt_find(BinTree* bt, int key) {
    return *bt_find_link(bt, key);
}

void bt_remove(BinTree* bt, int key) {
    BinTreeNode** link = bt_find_link(bt, key);

    if(*link == NULL) return; // key nicht enthalten
    bt_remove_link(bt, link);
}

void bt_remove_link(BinTree* bt, BinTreeNode** link) {
    // Falls zu loeschender Knoteon Grad 2 hat: Tausche mit
    // Vorgaengerknoten. Vorgaengerknoten hat Grad 0 oder Grad 1.
    if((*link)->left && (*link)->right) {
        BinTreeNode** pred = _pred(*link);
        (*link)->key = (*pred)->key;
        link = pred;
    }

    if(!(*link)->left && !(*link)->right) {
        // Grad 0 Knoten
        bt_node_destroy(*link);
        free(*link);
        *link = NULL;
    }
    else if((*link)->left && !(*link)->right) {
        // Grad 1, linkes Kind existiert
        BinTreeNode* left_child = (*link)->left;
        bt_node_destroy(*link);
        free(*link);
        *link = left_child;
    }
    else {
        // Grad 1, rechtes Kind existiert
        BinTreeNode* right_child = (*link)->right;
        bt_node_destroy(*link);
        free(*link);
        *link = right_child;
    }

    bt->size--;
}

BinTreeNode* bt_add_rec(BinTree* bt, int key) {
    if(!bt->root) {
        bt->root = create_bt_node(key);
        bt->size++;
        return bt->root;
    }

    return _bt_add_rec(bt, bt->root, key);
}

BinTreeNode* _bt_add_rec(BinTree* bt, BinTreeNode* v, int key) {
    if(key == v->key) return v;

    if(key < v->key) {
        if(v->left) {
            _bt_add_rec(bt, v->left, key);
        }
        else {
            v->left = create_bt_node(key);
            bt->size++;
            return v->left;
        }
    }
    else {
        if(v->right) {
            _bt_add_rec(bt, v->right, key);
        }
        else {
            v->right = create_bt_node(key);
            bt->size++;
            return v->right;
        }
    }

    return NULL; // never reached
}

BinTreeNode* bt_add_rec2(BinTree* bt, int key) {
    return _bt_add_rec2(bt, &bt->root, key);
}

BinTreeNode* _bt_add_rec2(BinTree* bt, BinTreeNode** link, int key) {
    if(!*link){
        *link = create_bt_node(key);
        bt->size++;
    }
    if((*link)->key == key) return *link;

    if(key < (*link)->key){
        return _bt_add_rec2(bt, &( (*link)->left ), key);
    }
    else{
        return _bt_add_rec2(bt, &( (*link)->right ), key);
    }
}

BinTreeNode* bt_add_non_rec(BinTree* bt, int key) {
    BinTreeNode** link = bt_find_link(bt, key);
    if(*link) return *link; // Schluessel schon enthalten

    *link = create_bt_node(key);
    bt->size++;
    return *link;
}


BinTreeNode** bt_find_link(BinTree* bt, int key) {
    BinTreeNode** link = &bt->root;

    while(*link && (*link)->key != key) {
        if(key < (*link)->key) {
            link = &( (*link)->left );
        }
        else if(key > (*link)->key) {
            link = &( (*link)->right );
        }
    }

    return link;
}

BinTreeNode** _pred(BinTreeNode* v) {
    if(!v) return NULL;

    BinTreeNode** pred = &(v->left);
    while( (*pred)->right ) {
        pred = &( (*pred)->right );
    }

    return pred;
}

void bt_print_as_dot(BinTree* bt, FILE* f) {
    fprintf(f, "digraph {\n");
    fprintf(f, "\tgraph [ordering=\"out\"];\n");
    _bt_print_as_dot_rec(bt->root, f);
    fprintf(f, "}\n");
}

void _bt_print_as_dot_rec(BinTreeNode* v, FILE* f) {
    if(!v) return;

    if(v->left){
        fprintf(f, "\t%d -> %d;\n", v->key, v->left->key);
    }
    else {
        fprintf(f, "\tnull%dl [shape=\"point\"];\n", v->key);
        fprintf(f, "\t%d -> null%dl;\n", v->key, v->key);
    }

    if(v->right){
        fprintf(f, "\t%d -> %d;\n", v->key, v->right->key);
    }
    else {
        fprintf(f, "\tnull%dr [shape=\"point\"];\n", v->key);
        fprintf(f, "\t%d -> null%dr;\n", v->key, v->key);
    }


    _bt_print_as_dot_rec(v->left, f);
    _bt_print_as_dot_rec(v->right, f);
}

void bt_print_preorder(BinTree* bt, FILE* f) {
    _bt_print_preorder(bt->root, f);
}

void _bt_print_preorder(BinTreeNode* v, FILE* f) {
    if(!v) return;

    fprintf(f, "%d ", v->key);
    _bt_print_preorder(v->left, f);
    _bt_print_preorder(v->right, f);
}

void bt_print_inorder(BinTree* bt, FILE* f) {
    _bt_print_inorder(bt->root, f);
}

void _bt_print_inorder(BinTreeNode* v, FILE* f) {
    if(!v) return;

    _bt_print_inorder(v->left, f);
    fprintf(f, "%d ", v->key);
    _bt_print_inorder(v->right, f);
}

void bt_print_postorder(BinTree* bt, FILE* f) {
    _bt_print_postorder(bt->root, f);
}

void _bt_print_postorder(BinTreeNode* v, FILE* f) {
    if(!v) return;

    _bt_print_postorder(v->left, f);
    _bt_print_postorder(v->right, f);
    fprintf(f, "%d ", v->key);
}
