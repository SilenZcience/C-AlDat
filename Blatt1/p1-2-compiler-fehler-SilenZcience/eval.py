from testers.outputtests import *
import io

def strip_newline(s):
    return s.replace('\r', '').replace('\n','')

class CompilerErrorTest(StatusTest):
    @staticmethod
    def _build_check_command(source_file, outfile, flags, error):
        return f"gcc {' '.join(flags)} -o {outfile} {source_file} 2>&1 | grep -E '{error}'"

    def __init__(self, source_file, outfile, flags, error, name="", description="", points=1, timeout=1):
        super().__init__(
            self._build_check_command(source_file, outfile, flags, error),
            name=name,
            description=description,
            points=points,
            timeout=timeout
        )

    def _process_returncode(self, p):
        if p.returncode == 1:
            self.status = Status.SUCCESS
        elif p.returncode == 0:
            self.status = Status.WRONG_OUTPUT
        else:
            self.status = Status.ERROR

tests = TestSuite("Aufgabe: Compilerfehler")
tests.add(CompilerErrorTest(
    "error.c",
    "error",
    ["-Wall", "-Werror"],
    "implicit declaration of function",
    name="implicit declaration",
    description="Alle Fehler 'implicit declaration of...' behoben?"
))

tests.add(CompilerErrorTest(
    "error.c",
    "error",
    ["-Wall", "-Werror"],
    "format .* expects argument of type",
    name="expected argument type",
    description="Alle Fehler 'format ... expects argument of type ...' behoben?"
))

tests.add(CompilerErrorTest(
    "error.c",
    "error",
    ["-Wall", "-Werror"],
    "return type of .* is not",
    name="return type of main",
    description="Alle Fehler 'return type of ... is not ...' behoben?"
))

tests.add(CompilerErrorTest(
    "error.c",
    "error",
    ["-Wall", "-Werror"],
    "undeclared",
    name="undeclared",
    description="Alle Fehler 'undeclared ...' behoben?"
))

tests.add(CompilerErrorTest(
    "error.c",
    "error",
    ["-Wall", "-Werror"],
    "left-hand operand of comma expression has no effect",
    name="comma expression",
    description="Alle Fehler 'left-hand operand of comma expression has no effect...' behoben?"
))

tests.add(CompilerTest(
    "error.c",
    "error",
    flags=["-Wall -Werror -DNDEBUG"],
    name="Programm compiliert",
    description="Compiliert der Quellcode mit -Wall ohne Fehler/Warnings?"
))

tests.add(CompareWithFileTest(
    "./error < testcases/test1.in",
    "testcases/test1.out",
    name="Richtige Ausgabe 1",
    description="Liefert Programm richtige Ausgabe auf Testfall 1?"
))

tests.add(CompareWithFileTest(
    "./error < testcases/test2.in",
    "testcases/test2.out",
    name="Richtige Ausgabe 2",
    description="Liefert Programm richtige Ausgabe auf Testfall 2?"
))

success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
