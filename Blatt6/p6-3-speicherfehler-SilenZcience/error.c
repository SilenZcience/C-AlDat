#include <stdio.h>
#include <stdlib.h>

typedef struct Foo{
    double* arr;
    int size;
} Foo;

int imin(int x, int y){
    return (x <= y ? x : y);
}

double* init_array(int n) {
    // we cannot return a local array, therefor we need
    // to allocate the memory and free it later.
    double* array = calloc(sizeof(double), n);
    for(int i=0; i < n; ++i) {
        // not sure if this makes a difference, but
        // probably better practice to cast to a double.
        array[i] = (double) i;
    }
    return array;
}

Foo* create_foo(int size) {
    // we cannot return a local struct, therefor we need
    // to allocate the memory and free it later.
    Foo* f = (Foo*) malloc(sizeof(Foo));
    f->arr = init_array(size);
    f->size = size;
    return f;
}

void print_foo(const Foo* f) {
    for(int i=0; i < f->size; ++i) {
        printf("%.3f", f->arr[i]);
    }
    printf("\n");
}

// in order to save memory we will pass pointers to this function
// instead of copying the entire struct.
Foo* add_foo(Foo* f1, Foo* f2) {
    int n = imin(f1->size, f2->size);
    // we need to remove the astrix of Foo* inside the sizeof() call,
    // because we want the size of the struct, not a pointer to the struct.
    Foo* sum = (Foo*) malloc(sizeof(Foo));
    // we need to initialize the array of the 'sum' Foo
    // before we access it in the following for loop.
    sum->arr = init_array(n);
    sum->size = n;

    for(int i=0; i < n; ++i) {
        sum->arr[i] = f1->arr[i] + f2->arr[i];
    }

    return sum;
}

int main(void) {
    const int n_foos = 10;
    const int foo_size = 5;

    Foo** foos = (Foo**) malloc(n_foos*sizeof(Foo*));
    for(int i=0; i < n_foos; ++i) {
        foos[i] = create_foo(foo_size);
    }

    for(int i=0; i < n_foos; ++i) {
        print_foo(foos[i]);
    }

    // because we changed the parameters of the function
    // we do not need to dereference the structs here.
    Foo* foo_sum = add_foo(foos[0], foos[1]);
    print_foo(foo_sum);
    // free the sum array and sum Foo
    free(foo_sum->arr);
    free(foo_sum);

    // free all foo-arrays, all foos, and the 'foos' variable itself.
    for (int i = 0; i < n_foos; i++) {
        free(foos[i]->arr);
        free(foos[i]);
    }
    free(foos);

    return 0;
}
