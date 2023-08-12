from testers.outputtests import *
import io

def strip_newline(s):
    return s.replace('\r', '').replace('\n','')

# für jede Eingabe:
# - Ein Test: enthält Zahlenmenge alle Primzahlen?
# - Ein Test: enthält Zahlenmenge keine nicht-Primzahl?
# - Ein Test: ist Ausgabe sortiert?

class OutputSubSetTest(StatusTest):
    def __init__(self, cmd, from_file, name="", description="", points=1, timeout=5):
        super().__init__(
            cmd,
            name=name,
            description=description,
            points=points,
            timeout=timeout
        )
        self.from_file = from_file

        self._err_stream=subprocess.STDOUT
        self._out_stream=subprocess.PIPE


    def _award_points(self):
        if self.status == Status.TIMEOUT or self.status == Status.ERROR:
            self.awarded_points = 0
            return

        with open(self.from_file) as exp_output_file:
            expected_output = { int(x) for x in exp_output_file.read().split() }

        try:
            usr_output = [int(x) for x in self.std_output.decode("UTF-8").split()]
            for x in usr_output:
                if not x in expected_output:
                    print(f"Zahl {x} nicht in Ausgabe erwartet.")
                    self.awarded_points = 0
                    self.status = Status.WRONG_OUTPUT
                    return

            self.awarded_points = self.total_points
            self.status = Status.SUCCESS


        except ValueError:
            print("Ausgabe enthält unzulässige Zeichen.")
            self.awarded_points = 0
            self.status = Status.WRONG_OUTPUT


class OutputSuperSetTest(StatusTest):
    def __init__(self, cmd, from_file, name="", description="", points=1, timeout=5):
        super().__init__(
            cmd,
            name=name,
            description=description,
            points=points,
            timeout=timeout
        )
        self.from_file = from_file

        self._err_stream=subprocess.STDOUT
        self._out_stream=subprocess.PIPE


    def _award_points(self):
        if self.status == Status.TIMEOUT or self.status == Status.ERROR:
            self.awarded_points = 0
            return

        with open(self.from_file) as exp_output_file:
            expected_output =  [int(x) for x in exp_output_file.read().split()]

        try:
            usr_output = { int(x) for x in self.std_output.decode("UTF-8").split() }
            for x in expected_output:
                if not x in usr_output:
                    print(f"Zahl {x} fehlt in der Ausgabe.")
                    self.awarded_points = 0
                    self.status = Status.WRONG_OUTPUT
                    return

            self.awarded_points = self.total_points
            self.status = Status.SUCCESS


        except ValueError:
            print("Ausgabe enthält unzulässige Zeichen.")
            self.awarded_points = 0
            self.status = Status.WRONG_OUTPUT

class IsSortedTest(StatusTest):
    def __init__(self, cmd, name="", description="", points=1, timeout=5):
        super().__init__(
            cmd,
            name=name,
            description=description,
            points=points,
            timeout=timeout
        )

        self._err_stream=subprocess.STDOUT
        self._out_stream=subprocess.PIPE

    @staticmethod
    def _is_sorted(l):
        for i,j in zip(l, l[1:]):
            if i > j:
                return False

        return True

    def _award_points(self):
        if self.status == Status.TIMEOUT or self.status == Status.ERROR:
            self.awarded_points = 0
            return

        try:
            usr_output = [int(x) for x in self.std_output.decode("UTF-8").split()]

            if not self._is_sorted(usr_output):
                print(f"Ausgabe ist nicht sortiert.")
                self.awarded_points = 0
                self.status = Status.WRONG_OUTPUT

            self.awarded_points = self.total_points
            self.status = Status.SUCCESS

        except ValueError:
            print("Ausgabe enthält unzulässige Zeichen.")
            self.awarded_points = 0
            self.status = Status.WRONG_OUTPUT

class CombinedTest:
    def __init__(self, tests, name="", description="", points=1, critical=False):
        self.name=name
        self.description=description
        self.tests = tests
        self.status = Status.ERROR
        self.awarded_points = 0
        self.total_points = points
        self.critical = critical

    def run(self):
        for t in self.tests:
            t.run()

        self._process_status()
        self._award_points()

    def _process_status(self):
        self.status = Status.SUCCESS
        for t in self.tests:
            if t.status != Status.SUCCESS:
                self.status = t.status
                return

    def _award_points(self):
        if self.status == Status.SUCCESS:
            self.awarded_points = 1
        else:
            self.awarded_points = 0


tests = TestSuite("Aufgabe: Primzahlen")

# add further tests here

tests.add(StatusTest(
    "make && test -f primes",
    name="Kompilieren+Linken",
    description="Klappt kompilieren/linken?",
    points=2,
    critical=True
))


tests.add(CompareWithFileTest(
    "./primes < testcases/test0.in", 
    "testcases/test0.out", 
    name="Keine Primzahl", 
    description="Wird nichts ausgegeben, wen es keine Primzahlen gibt?", 
    points=1
))


tests.add(OutputSubSetTest(
    "./primes < testcases/test1.in",
    "testcases/test1.out",
    name="T1: Alles prim?",
    description="Werden in Testfall 1 nur Primzahlen ausgegeben?",
    points=2
))

tests.add(OutputSuperSetTest(
    "./primes < testcases/test1.in",
    "testcases/test1.out",
    name="T1: Alle Primzahlen?",
    description="Enthält in Testfall 1 die Ausgabe alle Primzahlen?"
))

tests.add(OutputSubSetTest(
    "./primes < testcases/test2.in",
    "testcases/test2.out",
    name="T2: Alles prim?",
    description="Werden in Testfall 2 nur Primzahlen ausgegeben?",
    points=2
))

tests.add(OutputSuperSetTest(
    "./primes < testcases/test2.in",
    "testcases/test2.out",
    name="T2: Alle Primzahlen?",
    description="Enthält in Testfall 2 die Ausgabe alle Primzahlen?"
))

# tests.add(
#     IsSortedTest(
#     "./primes < testcases/test1.in",
#     name="T1: Ausgabe sortiert?",
#     description="Werden die Zahlen aufsteigend sortiert ausgegeben?"
# ))
#
#
# tests.add(IsSortedTest(
#     "./primes < testcases/test2.in",
#     name="T2: Ausgabe sortiert?",
#     description="Werden die Zahlen aufsteigend sortiert ausgegeben?"
# ))

tests.add(CombinedTest([
    IsSortedTest(
        "./primes < testcases/test1.in",
        name="T1: Ausgabe sortiert?",
        description="Werden die Zahlen aufsteigend sortiert ausgegeben?",
        points=0
    ),
    IsSortedTest(
        "./primes < testcases/test2.in",
        name="T2: Ausgabe sortiert?",
        description="Werden die Zahlen aufsteigend sortiert ausgegeben?",
        points=0
    )],
    name="T1+T2: Ausgabe sortiert?",
    description="Ist die Ausgabe in T1+T2 sortiert?"
))

success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
