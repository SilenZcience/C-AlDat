from testers.outputtests import *
import io

def strip_newline(s):
    return s.replace('\r', '').replace('\n','')

tests = TestSuite("Aufgabe: Headers")

# add further tests here
tests.add(CompareWithFileTest("cat main.c", "testcases/test0.in", name="main.c unveraendert?", description="Wurde main.c veraendert?", points=0))

tests.add(StatusTest("make fraction.o", name="Kompiliere fraction.c", description="Kompiliert fraction.c ohne Fehler?", points=2))
tests.add(StatusTest("make io.o", name="Kompiliere io.c", description="Kompiliert io.c ohne Fehler?", points=2))
tests.add(StatusTest("make genmath.o", name="Kompiliere genmath.c", description="Kompiliert genmath.c ohne Fehler?", points=2))

tests.add(StatusTest("make main.o", name="Kompiliere main.c", description="Kompiliert main.c ohne Fehler?", points=1))
tests.add(StatusTest("make", name="Linke...", description="Kann das Programm gelinkt werden?", points=1))
tests.add(CompareWithFileTest("./fracdemo < testcases/test1.in", "testcases/test1.out", name="Testfall 1", description="Ausgabe fuer Testfall 1 richtig?", points=1))
tests.add(CompareWithFileTest("./fracdemo < testcases/test2.in", "testcases/test2.out", name="Testfall 2", description="Ausgabe fuer Testfall 2 richtig?", points=1))

success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
