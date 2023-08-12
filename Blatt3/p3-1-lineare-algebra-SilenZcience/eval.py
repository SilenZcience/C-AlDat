from testers.outputtests import *
import io

def strip_newline(s):
    return s.replace('\r', '').replace('\n','')

tests = TestSuite("Aufgabe: Lineare Algebra")

tests.add(StatusTest("make pointmath.o io.o main.o", name="Erzeuge Objektdateien", description="Kompilieren pointmath.o, io.o, main.o ohne Fehler?", points=1))
#tests.add(StatusTest("make io.o", name="Kompiliere io.c", description="Kompiliert io.c ohne Fehler?", points=1))
#tests.add(StatusTest("make main.o", name="Kompiliere main.c", description="Kompiliert main.c ohne Fehler?", points=1))

tests.add(FindPatternTest("touch debug.h; make io.o", "gcc .* io.o", name="Dependencies io.c", description="Header von io.c richtig gesetzt?", points=1))
tests.add(FindPatternTest("touch point.h; make pointmath.o", "gcc .* pointmath.o", name="Dependencies pointmath.c", description="Header von pointmath.c richtig gesetzt?", points=1))
tests.add(FindPatternTest("touch point.h; make main.o", "gcc .* main.o", name="Dependencies main.c", description="Header von main.c richtig gesetzt?", points=1))

tests.add(StatusTest("make && test -f linalg", name="Kompilieren+Linken", description="Klappt kompilieren/linken?", points=2))
tests.add(StatusTest("./linalg < testcases/test1.in | grep '\[Debug\]'", name="Debugausgabe?", description="Wurde Debugausgabe aktiviert?", points=2))
tests.add(CompareWithFileTest(r"./linalg < testcases/test1.in | grep -v '\[Debug\]'", "testcases/test1.out", name="Testfall 1", description="Ausgabe fuer Testfall 1 richtig?", points=1))
tests.add(CompareWithFileTest(r"./linalg < testcases/test2.in | grep -v '\[Debug\]'", "testcases/test2.out", name="Testfall 2", description="Ausgabe fuer Testfall 2 richtig?", points=1))

# add further tests here

success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
