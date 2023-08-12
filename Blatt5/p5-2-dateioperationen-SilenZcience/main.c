#include <stdio.h>
#include <string.h>

const char* outfile_name = "numbers.out";

void print_error(int row, int col) {
    fprintf(stderr, "Fehler: Konnte Zeile %d nicht lesen: Fehler in Spalte %d.\n", row, col);
}

void write_array_to_file(FILE* out, int arr[], int n) {
    // write the given values to a given file pointer
    for (int i = 0; i < n; i++) {
        fprintf(out, "%d ", arr[i]);
    }
    fprintf(out, "\n");
}

int main(int argn, const char* args[]) {
    if(argn < 2) {
        fprintf(stderr, "Aufruf mit ./sum <Eingabedatei>\n");
        return 1;
    }

    // open input and output file, exit on error.
    FILE* file_in_pointer = fopen(args[1], "r");
    if (file_in_pointer == NULL) {
        printf("Error: Couldn't open file: %s\n", args[1]);
        return 2; /* stop execution when fopen() fails */
    }
    FILE* file_out_pointer = fopen(outfile_name, "w");
    if (file_out_pointer == NULL) {
        printf("Error: Couldn't open file: %s\n", outfile_name);
        return 3; /* stop execution when fopen() fails */
    }

    // initialize the row and col numbers, and scan them from the input file
    int m;
    int n;
    fscanf(file_in_pointer, "%d %d", &n, &m);

    // initialize column sum array and temporary column array
    // to 0 vlues. A simple for-loop would have been to exhausting :) ...
    int sum[m];
    int current_row[m];
    memset(sum, 0, m * sizeof(int));

    // iterate over the rows
    for (int i = 0; i < n; i++) {
        // iterate over the columns
        for (int j = 0; j < m; j++) {
            int matches = fscanf(file_in_pointer, "%d", &current_row[j]);
            // on error: print error for column and row number & close file handles
            if (matches != 1) {
                print_error(i+2, j+1);
                fclose(file_in_pointer);
                fclose(file_out_pointer);
                return 4;
            }
        }
        
        // update the column sum and print the values to stdout
        for (int j = 0; j < m; j++) {
            sum[j] += current_row[j];
            printf("%d ", sum[j]);
        }
        printf("\n");
    }
    
    // write the final result to the output file
    // and close the file handles
    write_array_to_file(file_out_pointer, sum, m);
    fclose(file_in_pointer);
    fclose(file_out_pointer);

    return 0;
}
