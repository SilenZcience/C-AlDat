from testers.outputtests import *
import io

class SortingTest(StatusTest):
    @staticmethod
    def _build_sort_command(cmd, infile):
        return f"{cmd} < {infile}"

    def __init__(self, cmd, infile, outfile, name="", description="", points=2, timeout=1):
        super().__init__(self._build_sort_command(cmd, infile), name, description, points, timeout)
        self.outfile = outfile

        self._err_stream=subprocess.STDOUT
        self._out_stream=subprocess.PIPE

    @staticmethod
    def _is_sorted(l):
        for i,j in zip(l, l[1:]):
            if i > j:
                return False

        return True

    def _award_points(self):
        self.awarded_points = 0

        if self.status == Status.TIMEOUT or self.status == Status.ERROR:
            return

        with open(self.outfile) as exp_output_file:
            expected_output = [int(x) for x in exp_output_file.read().split()]

        try:
            usr_output = [int(x) for x in self.std_output.decode("UTF-8").split()]

            # if len(usr_output) != len(expected_output):
            #     self.awarded_points = 0
            #     self.status = Status.WRONG_OUTPUT
            #     print("Ausgabe enthält nicht die richtige Zahlenmenge.")
            #     return
            #
            # if len(expected_output) == 0 and len(usr_output) == 0:
            #     self.awarded_points = self.total_points
            #     self.status = Status.SUCCESS
            #     return

            if not sorted(usr_output) == sorted(expected_output):
                self.awarded_points = 0
                self.status = Status.WRONG_OUTPUT
                print("Ausgabe enthält nicht die richtige Zahlenmenge.")
                return

            # ausgegeben Zahlenmenge ist richtig, 1 Punkt
            self.awarded_points = int(self.total_points / 2)

            if not self._is_sorted(usr_output):
                self.status = Status.WRONG_OUTPUT
                print("Ausgabe enthält die richtige Zahlenmenge, ist aber nicht sortiert.")
                return

            # # output is sorted; check if it contains the correct numbers
            # # both expected output and user output are _is_sorted; check if equal
            # for usr, exp in zip(usr_output, expected_output):
            #     if not usr == exp:
            #         self.awarded_points = 0
            #         self.status = Status.WRONG_OUTPUT
            #         print("Ausgabe enthält nicht die richtige Zahlenmenge.")
            #         return

            # Ausgabe ist sortiert und richtig, volle Punktzahl
            print("Ausgabe ist vollständig und sortiert")
            self.awarded_points = self.total_points
            self.status = Status.SUCCESS

        except ValueError:
            print("Ausgabe enthält unzulässige Zeichen.")
            self.awarded_points = 0
            self.status = Status.WRONG_OUTPUT

def strip_newline(s):
    return s.replace('\r', '').replace('\n','')

tests = TestSuite("Aufgabe: Insertion-Sort")
tests.add(CompilerTest(
    "insertionsort.c",
    "inssort",
    flags=["-Wall -DNDEBUG"],
    name="Programm compiliert",
    description="Compiliert der Quellcode mit -Wall ohne Fehler?",
    points=0
))

tests.add(SortingTest(
    "./inssort",
    f"tests/test1.in",
    f"tests/test1.out",
    name=f"Testfall 1",
    description=f"Programm sortiert Testfall 1."
))

tests.add(SortingTest(
    "./inssort",
    f"tests/test2.in",
    f"tests/test2.out",
    name=f"Testfall 2",
    description=f"Programm sortiert Testfall 2."
))

tests.add(SortingTest(
    "./inssort",
    f"tests/test3.in",
    f"tests/test3.out",
    name=f"Testfall 3",
    description=f"Programm sortiert Testfall 3.",
    points = 1
))

tests.add(SortingTest(
    "./inssort",
    f"tests/test4.in",
    f"tests/test4.out",
    name=f"Testfall 4",
    description=f"Programm sortiert Testfall 4.",
    points=1
))

tests.add(SortingTest(
    "./inssort",
    f"tests/test5.in",
    f"tests/test5.out",
    name=f"Testfall 5",
    description=f"Programm sortiert Testfall 5."
))

tests.add(SortingTest(
    "./inssort",
    f"tests/test6.in",
    f"tests/test6.out",
    name=f"Testfall 6",
    description=f"Programm sortiert Testfall 6."
))


# add further tests here

success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
