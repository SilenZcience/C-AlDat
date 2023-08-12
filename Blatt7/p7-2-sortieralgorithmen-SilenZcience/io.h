#ifndef CA_IO_H_
#define CA_IO_H_

#include <stdio.h>

/* Gibt Elemente aus Array A[l...r]  aus */
void print_subarray(FILE* f, int A[], int l, int r);

/* Gibt n Elemente aus Array A aus */
void print_array(FILE* f, int A[], int n);

/* Liest n ganze Zahlen in ein Array und gibt das Array zurück.
 *
 * Bei falschem Eingabeformat oder Lesefehlern wird NULL zurückgegeben.
 *
 * Gibt die Länge des Rückgabearrays in n zurück.
 *
 * Erwartetes Eingabeformat:
 *
 * <Anzahl Schlüssel>
 * <Schlüssel 1>
 * ...
 * <Schlüssel n>
 */
int* read_input(FILE* f, int* n);

#endif
