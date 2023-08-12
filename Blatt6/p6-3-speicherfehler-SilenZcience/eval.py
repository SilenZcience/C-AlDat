from testers.outputtests import *
import io
import re

class CountCommentsTest(StatusTest):
    def _count_lines(self):
        usr_out = self.std_output.decode("UTF-8")
        print(usr_out)
        n_marked = len(re.findall(r"//", usr_out))
        print(f"** {n_marked} Fehler markiert. **")
        return n_marked

    def __init__(self, cmd, expected_n_comments, name="", description="", points=1, timeout=1):
        super().__init__(
            cmd,
            name=name,
            description=description,
            points=points,
            timeout=timeout
        )
        self.expected_n_comments = expected_n_comments
        self._err_stream=subprocess.STDOUT
        self._out_stream=subprocess.PIPE

    def _award_points(self):
        if self.status == Status.TIMEOUT or self.status == Status.ERROR:
            self.awarded_points = 0
            return

        if not self._count_lines() == self.expected_n_comments:
            self.status = Status.WRONG_OUTPUT
            self.awarded_points = 0
        else:
            self.status = Status.SUCCESS
            self.awarded_points = self.total_points

tests = TestSuite("Aufgabe: Hashtable")

# add further tests here
tests.add(StatusTest(
    "make && test -f memerror",
    name="Kompilieren+Linken",
    description="Klappt kompilieren/linken?",
    points=0,
    critical=True
))

tests.add(ValgrindTest(
    r"./memerror",
    name="Speicherfehler?",
    points=0
))

tests.add(CountCommentsTest(
    r"grep -A1 '//' error.c",
    8,
    name="Welche Fehler markiert?",
    description="Welche Fehler wurden markiert?",
    points=0
))

success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
