from testers.outputtests import *
import io
import re

tests = TestSuite("Aufgabe: Projektmanagement")

# add further tests here
tests.add(StatusTest(
    "make && test -f pm",
    name="Kompilieren+Linken",
    description="Klappt kompilieren/linken?",
    points=0,
    critical=True
))

timeout=5
timeout_valgrind=20

names = [
    "Reihenfolge der Teams eingehalten?",
    "Projekte nach Wert abgearbeitet?",
    "Kleiner Testfall",
    "Großer Testfall",
    "Ende mit aktiven Projekten?"
]

for i in range(1,6):
    tests.add(CompareWithFileTest(
        rf"./pm < testcases/test{i}.in",
        f"testcases/test{i}.out",
        name=names[i-1],
        timeout=timeout,
        points=1
    )),
    tests.add(ValgrindTest(
        rf"./pm < testcases/test{i}.in",
        name=f"{names[i-1]}: Speicher ok?",
        timeout=timeout_valgrind,
        points=1
    ))


success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
