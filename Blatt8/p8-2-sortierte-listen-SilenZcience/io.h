#ifndef CA_IO_H_
#define CA_IO_H_

#include "dlinkedlist.h"

#include <stdio.h>

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
DList* read_input(FILE* f);

#endif
