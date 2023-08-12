from testers.outputtests import *
import io
import re

tests = TestSuite("Aufgabe: Hashtable")

# add further tests here
tests.add(StatusTest(
    "make && test -f arraylist",
    name="Kompilieren+Linken",
    description="Klappt kompilieren/linken?",
    points=0,
    critical=True
))

tests.add(CombinedTest([
    CompareWithFileTest(
        r"./arraylist < testcases/test1.in",
        "testcases/test1.out",
        name="Append ohne resize: Liste korrekt?",
        points=0
    ),
    ValgrindTest(
        r"./arraylist < testcases/test1.in",
        name="Append ohne resize: Speicherfehler?",
        points=0
    )],
    name="Append ohne resize",
    description="Append mit hinreichend grosser Liste.",
    points=1
))

tests.add(CombinedTest([
    CompareWithFileTest(
        r"./arraylist < testcases/test2.in",
        "testcases/test2.out",
        name="Insert am Ende: Korrekt?",
        points=0
    ),
    ValgrindTest(
        r"./arraylist < testcases/test2.in",
        name="Insert am Ende: Speicherfehler?",
        points=0
    )],
    name="Insert am Ende",
    description="Insert am Ende einer hinreichend großen Liste.",
    points=1
))

tests.add(CombinedTest([
    CompareWithFileTest(
        r"./arraylist < testcases/test3.in",
        "testcases/test3.out",
        name="Insert in Mitte: Korrekt?",
        points=0
    ),
    ValgrindTest(
        r"./arraylist < testcases/test3.in",
        name="Insert in Mitte: Speicherfehler?",
        points=0
    )],
    name="Insert in Mitte",
    description="Insert in die Mitte einer hinreichend großen Liste.",
    points=1
))

tests.add(CombinedTest([
    CompareWithFileTest(
        r"./arraylist < testcases/test4.in",
        "testcases/test4.out",
        name="Insert am Anfang: Korrekt?",
        points=0
    ),
    ValgrindTest(
        r"./arraylist < testcases/test4.in",
        name="Insert am Anfang: Speicherfehler?",
        points=0
    )],
    name="Insert am Anfang",
    description="Insert am Anfang einer hinreichend großen Liste.",
    points=1
))

tests.add(CombinedTest([
    CompareWithFileTest(
        r"./arraylist < testcases/test5.in",
        "testcases/test5.out",
        name="Append mit resize: Korrekt?",
        points=0
    ),
    ValgrindTest(
        r"./arraylist < testcases/test5.in",
        name="Append mit resize: Speicherfehler?",
        points=0
    )],
    name="Append mit resize",
    description="Append mit Liste, die vergrößert werden muss.",
    points=1
))


tests.add(CombinedTest([
    CompareWithFileTest(
        r"./arraylist < testcases/test6.in",
        "testcases/test6.out",
        name="Delete am Ende: Korrekt?",
        points=0
    ),
    ValgrindTest(
        r"./arraylist < testcases/test6.in",
        name="Delete am Ende: Speicherfehler?",
        points=0
    )],
    name="Delete am Ende",
    description="Löschen des letzten Elementes der Liste, kein resize.",
    points=1
))

tests.add(CombinedTest([
    CompareWithFileTest(
        r"./arraylist < testcases/test7.in",
        "testcases/test7.out",
        name="Delete am Anfang: Korrekt?",
        points=0
    ),
    ValgrindTest(
        r"./arraylist < testcases/test7.in",
        name="Delete am Anfang: Speicherfehler?",
        points=0
    )],
    name="Delete am Anfang",
    description="Löschen des ersten Elements der Liste, kein resize.",
    points=1
))

tests.add(CombinedTest([
    CompareWithFileTest(
        r"./arraylist < testcases/test8.in",
        "testcases/test8.out",
        name="Delete aus Mitte: Korrekt?",
        points=0
    ),
    ValgrindTest(
        r"./arraylist < testcases/test8.in",
        name="Delete aus Mitte: Speicherfehler?",
        points=0
    )],
    name="Delete aus Mitte",
    description="Löschen aus der Mitte der Liste, kein resize.",
    points=1
))


tests.add(CombinedTest([
    CompareWithFileTest(
        r"./arraylist < testcases/test9.in",
        "testcases/test9.out",
        name="Delete mit resize: Korrekt?",
        points=0
    ),
    ValgrindTest(
        r"./arraylist < testcases/test9.in",
        name="Delete mit resize: Speicherfehler?",
        points=0
    )],
    name="Delete mit resize",
    description="Delete mit Verkleinerung der Liste.",
    points=1
))


tests.add(CombinedTest([
    CompareWithFileTest(
        r"./arraylist < testcases/test10.in",
        "testcases/test10.out",
        name="Mehrfaches vergrößern/verkleinern: Korrekt?",
        points=0
    ),
    ValgrindTest(
        r"./arraylist < testcases/test10.in",
        name="Mehrfaches vergrößern/verkleinern: Speicherfehler?",
        points=0
    )],
    name="Mehrfaches resize",
    description="Append/Delete mit mehrfacher Vergrößerung/Verkleinerung der Liste.",
    points=1
))

success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
