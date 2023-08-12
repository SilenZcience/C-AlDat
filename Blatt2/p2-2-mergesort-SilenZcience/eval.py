from testers.outputtests import *
import io

def strip_newline(s):
    return s.replace('\r', '').replace('\n','')

tests = TestSuite("Aufgabe: Meine Aufgabe")
tests.add(CompilerTest(
    "mergesort.c",
    "mergesort",
    flags=["-Wall"],
    name="Programm compiliert",
    description="Compiliert der Quellcode mit -Wall ohne Fehler?",
    points=0
))

# add further tests here

for i in range(1, 9):
    tests.add(CompareWithFileTest(
        f"./mergesort < testcases/test{i}.in",
        f"testcases/test{i}.out",
        f"Beispiel {i}"
    ))

success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
