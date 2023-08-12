from testers.outputtests import *
import io
import re

tests = TestSuite("Aufgabe: Tokenizer")

# add further tests here
tests.add(StatusTest(
    "make && test -f tokenizer",
    name="Kompilieren+Linken",
    description="Klappt kompilieren/linken?",
    points=0,
    critical=True
))

tests.add(
    CompareWithFileTest(
        r"./tokenizer < testcases/test1.in",
        "testcases/test1.out",
        name="Keine Trennzeichen: Korrekt?",
        description="String ohne Trennzeichen: Korrektheit?",
        points=1
    )
)

tests.add(
    ValgrindTest(
        r"./tokenizer < testcases/test1.in",
        name="Keine Trennzeichen: Speicher?",
        description="String ohne Trennzeichen: Speicherfehler?",
        points=1
    )
)

tests.add(
    CompareWithFileTest(
        r"./tokenizer < testcases/test2.in",
        "testcases/test2.out",
        name="Mehrere Trennzeichen: Korrekt?",
        description="String mit mehreren Trennzeichen: Korrektheit?",
        points=1
    )
)

tests.add(
    ValgrindTest(
        r"./tokenizer < testcases/test2.in",
        name="Mehrere Trennzeichen: Speicher?",
        description="String mit mehreren Trennzeichen: Speicherfehler?",
        points=1
    )
)

tests.add(
    CompareWithFileTest(
        r"./tokenizer < testcases/test3.in",
        "testcases/test3.out",
        name="Trennzeichen am Ende: Korrekt?",
        description="String mit Trennzeichen am Ende: Korrektheit?",
        points=1
    )
)

tests.add(
    ValgrindTest(
        r"./tokenizer < testcases/test3.in",
        name="Trennzeichen am Ende: Speicher?",
        description="String mit Trennzeichen am Ende: Speicherfehler?",
        points=1
    )
)

tests.add(
    CompareWithFileTest(
        r"./tokenizer < testcases/test4.in",
        "testcases/test4.out",
        name="Trennzeichen am Anfang: Korrekt?",
        description="String mit Trennzeichen am Anfang: Korrektheit?",
        points=1
    )
)

tests.add(
    ValgrindTest(
        r"./tokenizer < testcases/test4.in",
        name="Trennzeichen am Anfang: Speicher?",
        description="String mit Trennzeichen am Anfang: Speicherfehler?",
        points=1
    )
)

tests.add(
    CompareWithFileTest(
        r"./tokenizer < testcases/test5.in",
        "testcases/test5.out",
        name="Leere Tokens: Korrekt?",
        description="String mit leeren Tokens: Korrektheit?",
        points=1
    )
)

tests.add(
    ValgrindTest(
        r"./tokenizer < testcases/test5.in",
        name="Leere Tokens: Speicher?",
        description="String mit leeren Tokens: Speicherfehler?",
        points=1
    )
)

success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
