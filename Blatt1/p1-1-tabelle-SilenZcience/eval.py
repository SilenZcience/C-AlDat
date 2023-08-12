from testers.outputtests import *
import io

def strip_newline(s):
    return s.replace('\r', '').replace('\n','')

class CompareTableTest(CompareOutputTest):
    def __init__(self, cmd, name="", description="", timeout=1):
        super().__init__(
            cmd,
            None, 
            comparer=None, 
            name=name, 
            description=description,
            points=8,
            timeout=timeout
        )

    def _award_points(self):
        if self.status == Status.TIMEOUT or self.status == Status.ERROR:
            self.awarded_points = 0
            return

        if self.std_output == None:
            self.awarded_points = 0
            self.status = Status.WRONG_OUTPUT
            print("## Ausgabe ist leer.")
            return

        output_str = io.StringIO(self.std_output.decode("UTF-8"))
        # we ignore the table header in this test case
        first_line = output_str.readline()
        print(first_line, end="")

        correct_entries = 0
        i = 0
        for line in output_str:
            row = line.split()
            i += 1

            line_correct = True

            try:
                if int(row[1].strip()) == i*i:
                    correct_entries += 1
                else:
                    line_correct = False

                if abs(float(row[2].strip()) - 1.0/i) <= 0.1:
                    correct_entries += 1
                else:
                    line_correct = False

            except:
                line_correct = False

            if line_correct:
                print(f"{strip_newline(line)} ✔")
            else:
                print(f"{strip_newline(line)} 🞬")

        for j in range(i+1,13):
            print(f"Zeile {j} fehlt. 🞬")

        if correct_entries < 24:
            self.status = Status.WRONG_OUTPUT

        self.awarded_points = int(correct_entries / 3)

tests = TestSuite("Aufgabe: Tabelle")
tests.add(CompilerTest(
    "table.c",
    "table",
    flags=["-Wall -DNDEBUG"],
    name="Programm compiliert",
    description="Compiliert der Quellcode mit -Wall ohne Fehler?",
    points = 1
))

tests.add(CompareTableTest(
    "./table",
    name="Spalten richtig", 
    description="Stimmt Inhalt der Spalten ungefähr?"
))

tests.add(CompareWithFileTest(
    "./table",
    "testcases/table.out",
    name="Tabelle richtig",
    description="Ist die Ausgabe *exakt* richtig?",
    points=1
))

success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
