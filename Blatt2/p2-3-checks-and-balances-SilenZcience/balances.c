#include <stdio.h>
#include <stdbool.h>

struct Bill {
    int id;
    int amount;
    bool paid;
};

// siehe P2-1
int bin_search(struct Bill A[], int n, int x) {
    int left = 0;
    int right = n-1;

    while (left <= right) {
        int mid = (left+right) / 2;
        if (A[mid].id < x) {
            left = mid + 1;
        }
        else if (A[mid].id > x) {
            right = mid - 1;
        }
        else {
            return mid;
        }
    }

    return n;
}

// siehe P2-2
void merge(struct Bill A[], int l, int m, int r, struct Bill H[]) {
    // kopiere A in Hilfsarray
    for(int i=l; i <= r; ++i) { 
        H[i] = A[i];
    }

    int out_pos = l; // Schreibposition in A
    int l_pos = l;   // Leseposition linker Teil
    int r_pos = m+1; // Leseposition rechter Teil

    // verschmelze bis eines der Teilarrays leer ist
    while(l_pos <= m && r_pos <= r) {
        if(H[l_pos].id < H[r_pos].id){
            A[out_pos] = H[l_pos];
            ++l_pos;
        }
        else {
            A[out_pos] = H[r_pos];
            ++r_pos;
        }
        ++out_pos;
    }

    while(l_pos <= m) {
        A[out_pos] = H[l_pos];        
        ++l_pos;
        ++out_pos;
    }
}

// siehe P2-2
/* ruft MergeSort auf Teilarray A[l...r] auf */
void merge_sort_(struct Bill A[], int l, int r, struct Bill H[]) {
    if(l < r) {
        const int m = (l+r) / 2;
        merge_sort_(A, l, m, H);
        merge_sort_(A, m+1, r, H);
        merge(A, l, m, r, H);
    }
}

// siehe P2-2
/* ruft MergeSort auf Array a mit n Elementen auf */
void merge_sort(struct Bill A[], int n) {
    struct Bill H[n]; // Hilfsarray
    merge_sort_(A, 0, n-1, H);
}

int read_input_bills(struct Bill A[], int n, int m) {
    // read in the id and amount of each bill; set the paid boolean
    // to default/false
    int id;
    int amount;

    for (int i = 0; i < n; i++) {
        if(scanf("%d %d", &id, &amount) == 0){
            printf("Fehler!\n");
            return 2;
        } 
        A[i].id = id;
        A[i].amount = amount;
        A[i].paid = false;
    }

    // the output expects to be sorted anyways, and by
    // sorting the array here (by id) we can use binary search
    // for setting the paid-boolean state to true for each
    // paid bill, resuling in a better performance ( O(nlogn) )
    merge_sort(A, n);

    // read in each paid bill, we actually only care about the id
    // under the assumption that each bill is paid in full.
    // find the corresponding bill with binary search and set the
    // paid value to true
    for (int i = 0; i < m; i++) {
        if(scanf("%d %d", &id, &amount) == 0){
            printf("Fehler!\n");
            return 3;
        }

        int index = bin_search(A, n, id);
        if (index < n) {
            A[index].paid = true;
        }
    }

    return 0;
}

int main(void) {
    //read in the amount of bills and paid bills
    int n;
    int m;
    if(scanf("%d %d", &n, &m) == 0) {
        printf("Fehler!\n");
        return 1;
    }

    // declare an array of struct Bill for each bill
    struct Bill bills[n];
    
    // populate the struct values for each bill
    int error = read_input_bills(bills, n, m);
    if(error > 0) {
        return error;
    }

    // calculate the debt and print out each
    // unpaid bill
    int debt = 0;

    for (int i = 0; i < n; i++) {
        if (bills[i].paid == false) {
            printf("%d\n", bills[i].id);
            debt += bills[i].amount;
        }
    }
    // print out the resulting debt sum
    printf("%d\n", debt);

    return 0;
}


