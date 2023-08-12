#include <stdio.h>

typedef struct Foo {
    double v;
} Foo;

void init_foo(Foo* foo, double v) {
    // foo ist ein Pointer, wir müssen also entweder (*foo).v 
    // oder foo->v benutzen.
    foo->v = v;
}

// damit x durch pass-by-reference tatsächlich seinen wert
// ändert, und nicht kopiert wird, müssen wir einen Pointer
// übergeben. Kenntlich durch das * nach dem Datentyp.
void cut_in_half(double* x) {
    *x = *x / 2.0;
}

int main(void) {
    // wir deklarieren Foo f als struct und nicht als Pointer.
    Foo f;
    init_foo(&f, 1.0);

    printf("%.3f\n", f.v);

    Foo g;
    // die Methode init_foo erwartet einen Pointer, und
    // keine Kopie des structs.
    init_foo(&g, 2.0);

    printf("%.3f\n", g.v);

    int a = 10;
    // um die Adresse von a zu erhalten müssen wir a mit dem
    // &-operanden referenzieren.
    int* pa = &a;

    // wir möchten den wert von a ausgeben, nicht die Adresse.
    // Entsprechend müssen wir den Pointer dereferenzieren.
    printf("%d\n", *pa);

    double x;
    cut_in_half(&x);
    printf("%.3f\n", x);

    const double e = 2.718;
    // wir möchten einen Pointer auf einen konstanten Wert,
    // nicht einen Pointer auf eine konstante Adresse.
    const double* pe = &e;
    printf("%.3f\n", *pe);

    int pi = 3;
    // damit wir den Wert, auf den der Pointer zeigt, verändern
    // können, darf das Schlüsselwort 'const' nicht vor dem
    // Datentyp stehen.
    // Theoretisch können wir auch 'int* const ppi = &pi;'
    // schreiben, wenn wir einen konstanten Pointer haben wollen.
    int* ppi = &pi;
    *ppi = 20;
    printf("%d\n", *ppi);

    char c = 'x';
    char* pc = &c;
    // Wir möchten den Wert ändern, auf den der Pointer zeigt,
    // nicht den Pointer selbst. Daher müssen wir pc
    // zunächst derefenzieren.
    *pc = 'y';
    printf("%c\n", *pc);

    return 0;
}
