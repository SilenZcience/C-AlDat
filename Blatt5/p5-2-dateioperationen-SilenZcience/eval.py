from testers.outputtests import *

def diff_file_command(cmd, f1, f2):
        return f"{cmd} && diff -y -b -B -Z --strip-trailing-cr -s --suppress-common-lines {f1} {f2}"

tests = TestSuite("Aufgabe: Union-Find")
tests.add(StatusTest(
        "make",
        name="Kompilieren und Linken?",
        description="Funktioniert 'make'?",
        points = 0,
        critical=True
))

tests.add(RuntimeErrorTest(
    r"./sum testcases/numbers4.in > /dev/null",
    name="Keine Runtime Error",
    description="Programm wirft keine Runtime Error mit -fsanitize?",
    points=0
))

tests.add(CompareWithFileTest(
    r"./sum testcases/numbers1.in",
    "testcases/numbers1.cout",
    name="Testfall 1: Konsolenausgabe?",
    description="Wird triviale Spaltensumme korrekt auf Konsole ausgegeben??"
))

tests.add(StatusTest(
    diff_file_command("./sum testcases/numbers1.in", "numbers.out", "testcases/numbers1.cout"),
    name="Testfall 1: Dateiausgabe?",
    description="Wird triviale Spaltensumme korrekt in Datei ausgegeben??"
))

tests.add(CompareWithFileTest(
    r"./sum testcases/numbers2.in",
    "testcases/numbers2.cout",
    name="Testfall 2: Konsolenausgabe?",
    description="Wird nicht-triviale Spaltensumme korrekt auf Konsole ausgegeben?"
))

tests.add(StatusTest(
    diff_file_command("./sum testcases/numbers2.in", "numbers.out", "testcases/numbers2.out"),
    name="Testfall 2: Dateiausgabe?",
    description="Funktioniert nicht-triviale Dateiausgabe?"
))


tests.add(CompareWithFileTest(
    r"./sum testcases/numbers3.in",
    "testcases/numbers3.cout",
    name="Testfall 3: Konsolenausgabe?",
    description="Werden kompliziertere Summen korrekt auf Konsole ausgegeben?"
))

tests.add(StatusTest(
    diff_file_command("./sum testcases/numbers3.in", "numbers.out", "testcases/numbers3.out"),
    name="Testfall 3: Dateiausgabe?",
    description="Werden kompliziertere Summen korrek in Datei ausgegeben?"
))

tests.add(CompareWithFileTest(
    r"./sum testcases/numbers4.in",
    "testcases/numbers4.cout",
    name="Testfall 4: Konsolenausgabe?",
    description="Funktionieren große Eingaben?"
))

tests.add(StatusTest(
    diff_file_command("./sum testcases/numbers4.in", "numbers.out", "testcases/numbers4.out"),
    name="Testfall 4: Dateiausgabe?",
    description="Funktionieren große Eingaben?"
))

tests.add(StatusTest(
    "./sum testcases/numbers5.in 2>&1 | grep -E 'Fehler:.+Zeile 31.+Spalte 5'",
    name="Fehlererkennung?",
    description="Werden Fehler in der Eingabe korrekt erkannt?"
))

tests.add(StatusTest(
    "grep -E 'fclose' main.c",
    name="Dateien geschlossen?",
    description="Werden Dateien geschlossen?"
))

success = tests.run()
if not success:
    exit(1)
else:
    exit(0)

