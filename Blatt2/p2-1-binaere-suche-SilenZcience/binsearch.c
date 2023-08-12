#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/* Testet, ob A[l...r] aufsteigend sortiert ist. */
bool is_sorted(int A[], int n) {
    
    // an array of length 1 is always sorted. we make this check,
    // so we can iterate through the array starting at index 1.
    if (n == 1) return true;

    for (int i = 1; i < n; i ++) {
        if (A[i-1] >= A[i]) return false;
    }

    return true;
}

/* Liest n ganze Zahlen in ein Array mit mindestens n Plätzen.
 *
 * Rückgabe: 0 falls erfolgreich, Fehlercode > 0 sonst.
 *
 * Erwartetes Eingabeformat:
 *
 * <Anzahl Schlüssel>
 * <Schlüssel 1>
 * ...
 * <Schlüssel n>
 */
int read_array(int A[], int n) {
    int n_read=0;
    while(n_read < n) {
        int num;

        // scanf liest aus 'virtueller' Datei stdin ("Konsoleneingabe")
        if(scanf("%d", &num) < 1){
            // teste, ob Dateiende erreicht
            if(feof(stdin)) {
                printf("Falsches Eingabeformat. ");
                printf("%d Schlüssel erwartet, aber nur %d Schlüssel gefunden.\n", n, n_read);
                return 2;
            }

            // teste, ob sonstiger Fehler
            if(ferror(stdin)){
                printf("Ein-/Ausgabefehler.\n");
                return 3;
            }

            // ansonsten: Zeile konnte nicht geparst werden
            printf("Falsches Eingabeformat. ");
            printf("Zeile %d: Ganze Zahl erwartet.\n", n_read+2);
            return 4;
        }

        // erfolgreich gelesen
        A[n_read++] = num;
    }

    return 0;
}

/* Sucht x in Array A mit Länge n. Gibt Position von x in A zurück, falls x
 * in A enthalten; sonst n.
 *
 * Annahme: A ist aufsteigend sortiert und enthält eindeutige Schlüssel.
 *
 * Wirft assertion falls A nicht aufsteigend sortiert ist.
 */
int bin_search(int A[], int n, int x) {
    // not much to say: basic implementation of the
    // lecture pseudo code.

    int left = 0;
    int right = n-1;

    while (left <= right) {
        int mid = (int) ((left+right) / 2);
        if (A[mid] < x) {
            left = mid + 1;
        }
        else if (A[mid] > x) {
            right = mid - 1;
        }
        else {
            return mid;
        }
        
        
    }

    return n;
}

/* Erwartetes Eingabeformat:
 *
 * <Suchschlüssel>
 * <Anzahl Schlüssel n>
 * <Schlüssel 1>
 * ...
 * Schlüssel n>
 */
int main(void) {
    int n;
    int x;
    if(scanf("%d", &x) != 1) {
        printf("Falsches Eingabeformat.\n");
        printf("Zeile 1: Ganze Zahl (Suchschlüssel) erwartet.\n");
        return 1;
    }

    if(scanf("%d", &n) < 1) {
        printf("Falsches Eingabeformat.\n");
        printf("Zeile 2: Ganze Zahl (Anzahl Schlüssel) erwartet.\n");
        return 1;
    }

    int A[n]; // Eingabearray
    int error;
    error = read_array(A, n);
    if(error > 0) {
        return error;
    }

    // if the input is not sorted we return error code 5
    // and print out the specific required assertion message
    // if(!is_sorted(A, n)) {
    //     printf("Assertion .* failed.");
    //     return 5;
    // }
    assert(is_sorted(A, n));

    printf("%d\n", bin_search(A, n ,x));

    return 0;
}
