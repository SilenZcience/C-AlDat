from testers.outputtests import *
import io

def strip_newline(s):
    return s.replace('\r', '').replace('\n','')

class CompilerErrorTest(StatusTest):
    @staticmethod
    def _build_check_command(error):
        return f"touch main.c && make 2>&1 | grep -q -E '{error}'"

    def __init__(self, error, name="", description="", points=1, timeout=1):
        super().__init__(
            self._build_check_command(error),
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

tests = TestSuite("Aufgabe: Zeigerfehler")
tests.add(CompilerErrorTest(
    r"error: ‘foo’ is a pointer; did you mean to use ‘->’?",
    name="Fehler 1",
    description="Fehler 1 behoben?"
))

tests.add(CompilerErrorTest(
    r"error: incompatible type for argument 1 of ‘cut_in_half’",
    name="Fehler 2",
    description="Fehler 2 behoben?"
))

tests.add(CompilerErrorTest(
    r"error: passing argument 1 of ‘init_foo’ from incompatible pointer type?",
    name="Fehler 3",
    description="Fehler 3 behoben?"
))

tests.add(CompilerErrorTest(
    r"error: incompatible type for argument 1 of ‘init_foo’",
    name="Fehler 4",
    description="Fehler 4 behoben?"
))

tests.add(CompilerErrorTest(
    r"error: initialization of ‘int \*’ from ‘int’ makes pointer from integer without a cast ",
    name="Fehler 5",
    description="Fehler 5 behoben?"
))

tests.add(CompilerErrorTest(
    r"error: format ‘%d’ expects argument of type ‘int’, but argument 2 has type ‘int \*’",
    name="Fehler 6",
    description="Fehler 6 behoben?"
))

tests.add(CompilerErrorTest(
    r"error: initialization discards ‘const’ qualifier from pointer target type",
    name="Fehler 7",
    description="Fehler 7 behoben?"
))

tests.add(CompilerErrorTest(
    r"error: assignment of read-only location ‘\*ppi’",
    name="Fehler 8",
    description="Fehler 8 behoben?"
))

tests.add(CompilerErrorTest(
    r"error: assignment to ‘char \*’ from ‘int’ makes pointer from integer without a cast",
    name="Fehler 9",
    description="Fehler 9 behoben?"
))

tests.add(StatusTest(
    "make && test -f pointererror",
    name="Kompilieren+Linken",
    description="Klappt kompilieren/linken?",
    points=0,
    critical=True
))

tests.add(CompareWithFileTest(
    r"./pointererror",
    "testcases/test.out",
    name="Ausgabe erhalten",
    description="Ist richtige Ausgabe erhalten geblieben?"
))

tests.add(StatusTest(
    r"grep '//' main.c && grep '//' main.c | wc -l | grep 9",
    name="Neun Fehler markiert?",
    description="Wurden neun Fehler markiert?",
    points=0
))


tests.run()
