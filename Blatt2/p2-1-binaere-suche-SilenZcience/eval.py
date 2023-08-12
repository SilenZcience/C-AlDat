from testers.outputtests import *
import io

def strip_newline(s):
    return s.replace('\r', '').replace('\n','')

tests = TestSuite("Aufgabe: Meine Aufgabe")
tests.add(CompilerTest(
    "binsearch.c",
    "binsearch",
    flags=["-Wall"],
    name="Programm compiliert",
    description="Compiliert der Quellcode mit -Wall ohne Fehler?",
    points=0
))

# add further tests here

for i in range(0, 8):
    tests.add(CompareWithFileTest(
        f"./binsearch < testcases/test{i}.in",
        f"testcases/test{i}.out",
        f"Beispiel {i}"
    ))

tests.add(FindPatternTest(
    "./binsearch < testcases/test8.in",
    "Assertion .* failed",
    "Beispiel 8"
))

tests.add(FindPatternTest(
    "./binsearch < testcases/test9.in",
    "Assertion .* failed",
    "Beispiel 9"
))

success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
