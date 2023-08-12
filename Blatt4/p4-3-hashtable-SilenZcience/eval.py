from testers.outputtests import *
import io
import re

tests = TestSuite("Aufgabe: Hashtable")

# add further tests here

tests.add(StatusTest(
    "make && test -f birds",
    name="Kompilieren+Linken",
    description="Klappt kompilieren/linken?",
    points=0,
    critical=True
))

tests.add(CompareWithFileTest(
    r"./birds < testcases/test1.in | grep -v 'Vogel\|Kollisionen'",
    "testcases/test1.out",
    name="Einfügen ohne Kollisionen",
    description="Geht einfügen ohne Kollisionen?"
))

tests.add(CompareWithFileTest(
    r"./birds < testcases/test2.in | grep -v 'Kollisionen'",
    "testcases/test2.out",
    name="Anfragen ohne Kollisionen",
    description="Funktionieren erfolgreiche Anfragen ohne Kollisionen?",
))

tests.add(StatusTest(
    r"./birds < testcases/test3.in | grep 'Vogel 10 nicht beobachtet'",
    name="Erfolglose Anfragen",
    description="Funktionieren Anfragen für nicht vorhandene Vögel?"
))

tests.add(CompareWithFileTest(
    r"./birds < testcases/test4.in | grep -v 'Vogel\|Kollisionen'",
    "testcases/test4.out",
    name="Einfügen mit Kollisionen",
    description="Geht einfügen mit Kollisionen?"
))

tests.add(CompareWithFileTest(
    r"./birds < testcases/test5.in | grep -v 'Kollisionen'",
    "testcases/test5.out",
    name="Anfragen mit Kollisionen",
    description="Funktionieren erfolgreiche Anfragen mit Kollisionen?"
))

tests.add(StatusTest(
    r"./birds < testcases/test5.in | grep '5 Kollisionen beim Einfügen.'",
    name="Zählen von Kollisionen",
    description="Werden Kollisionen korrekt gezählt?"
))

tests.add(CompareWithFileTest(
    r"./birds < testcases/test6.in",
    "testcases/test6.out",
    name="Wiederholte Kollisionen?",
    description="Funktioniert alles mit wiederholten Kollisionen?"
))

tests.add(CompareWithFileTest(
    r"./birds < testcases/test7.in",
    "testcases/test7.out",
    name="Komplexe Hashfunktion",
    description="Funktioniert alles mit komplexer Hashfunktion?"
))

tests.add(CompareWithFileTest(
    r"./birds < testcases/test8.in | grep -v 'Kollisionen'",
    "testcases/test8.out",
    name="Hashtabelle voll",
    description="Kann die Hashtabelle vollständig befüllt werden?"
))


#
# tests.add(StatusTest(
#     r"./birds < testcases/test9.in | grep 'Hashtabelle voll'",
#     name="Überfüllung?",
#     description="Fehler bei zu vielen Schlüsseln?"
# ))

tests.add(RuntimeErrorTest(
    r"./birds < testcases/test10.in > /dev/null",
    name="Keine Runtime Error",
    description="Programm wirft keine Runtime Error mit -fsanitize?"
))

success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
