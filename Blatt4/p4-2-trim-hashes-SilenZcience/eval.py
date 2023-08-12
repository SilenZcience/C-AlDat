from testers.outputtests import *
import io
import re

QUOTED_OUTPUT=re.compile(r"'(.*)'", flags=re.DOTALL)

def strip_newline(s):
    return s.replace('\r', '').replace('\n','')

def quoted_output_matcher(user, expected):
    user_output = user.decode("UTF-8")
    m = re.search(QUOTED_OUTPUT, user_output)
    if m == None:
        print("Ausgabe umschließt das Ergebnis nicht mit '...'")
        return False

    if f"'{m.group(1)}'" != expected.strip():
        print(f"Benutzerausgabe: '{m.group(1)}'    Erwartete Ausgabe: {expected.strip()}")
        return False

    print("Ausgabe korrekt.")
    return True


tests = TestSuite("Aufgabe: Trim-Hashes")

# add further tests here

tests.add(StatusTest(
    "make && test -f trim",
    name="Kompilieren+Linken",
    description="Klappt kompilieren/linken?",
    points=0,
    critical=True
))



try:
    tests.add(CompareWithFileContentTest(
        f"./trim < testcases/test1.in",
        f"testcases/test1.out",
        comparer=quoted_output_matcher,
        name="Eingabe bleibt heile",
        description="Eingabe ohne Hashes bleibt unverändert.",
        points=2
    ))

    tests.add(CompareWithFileContentTest(
        f"./trim < testcases/test2.in",
        f"testcases/test2.out",
        comparer=quoted_output_matcher,
        name="Leere Eingabe",
        description="Randfall: Leere Eingabe führt nicht zu Fehlern.",
        points=1
    ))

    tests.add(CompareWithFileContentTest(
        f"./trim < testcases/test3.in",
        f"testcases/test3.out",
        comparer=quoted_output_matcher,
        name="Hashes am Ende",
        description="Hashes am Ende werden abgeschnitten.",
        points=2
    ))

    tests.add(CompareWithFileContentTest(
        f"./trim < testcases/test4.in",
        f"testcases/test4.out",
        comparer=quoted_output_matcher,
        name="Hashes am Anfang",
        description="Hashes am Anfang werden abgeschnitten.",
        points=2
    ))

    tests.add(CompareWithFileContentTest(
        f"./trim < testcases/test5.in",
        f"testcases/test5.out",
        comparer=quoted_output_matcher,
        name="Hashes im String",
        description="Hashes in der Mitte vom String bleiben erhalten.",
        points=2
    ))

    tests.add(CompareWithFileContentTest(
        f"./trim < testcases/test6.in",
        f"testcases/test6.out",
        comparer=quoted_output_matcher,
        name="String aus #",
        description="Randfall: String, der nur aus # besteht.",
        points=1
    ))

except IOError as e:
    print(f"[Fehler in eval.py] Konnte Testfall {e.filename} nicht lesen: {e.strerror}.")

success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
