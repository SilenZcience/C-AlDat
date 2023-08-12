from testers.outputtests import *
import io
import re

class IncrementalTest(CombinedTest):
    def __init__(self, tests, name="", description="", points=1, critical=False):
        super().__init__(tests, name, description, points, critical)

    def _award_points(self):
        self.awarded_points = 0
        for t in self.tests:
            if t.status != Status.SUCCESS:
                break

            self.awarded_points += t.awarded_points

tests = TestSuite("Aufgabe: Sortierte Listen")

# add further tests here
tests.add(StatusTest(
    "make && test -f sortlist",
    name="Kompilieren+Linken",
    description="Klappt kompilieren/linken?",
    points=0,
    critical=True
))

tests.add(StatusTest(
    "make && test -f listtest",
    name="Kompilieren+Linken der Listentests",
    description="Klappt kompilieren/linken?",
    points=0,
    critical=True
))

list_test_names = [
    "verschieben aus der Mitte",
    "verschieben am Rand"
]

tests.add(CompareWithFileTest(
        rf"./listtest < testcases/listtest1.in",
        rf"testcases/listtest1.out",
        name=list_test_names[0],
        description="",
        points=1,
        timeout=10
    )
)

tests.add(IncrementalTest([
    CompareWithFileTest(
        rf"./listtest < testcases/listtest2.in",
        rf"testcases/listtest2.out",
        name=list_test_names[1],
        description="",
        points=1,
        timeout=10
    ),
    ValgrindTest(
        rf"./listtest < testcases/listtest2.in",
        name="Speicherfehler?",
        timeout=10
    )],
    name=list_test_names[1],
    points=2
))

test_names = [
    "Invertierte Folge",
    "Interleaved",
    "Anzahl prim",
    "Verdreht",
    "Speicherfehler?"
]

for num in range(1,4):
    tests.add(CompareWithFileTest(
            rf"./sortlist < testcases/test{num}.in",
            rf"testcases/test{num}.out",
            name=test_names[num-1],
            description="",
            points=1,
            timeout=10
        )
    )

tests.add(IncrementalTest([
    CompareWithFileTest(
        rf"./sortlist < testcases/test{num}.in",
        rf"testcases/test{num}.out",
        name=test_names[4],
        description="",
        points=1,
        timeout=10
    ),
    ValgrindTest(
        rf"./sortlist< testcases/test{num}.in",
        name="Speicherfehler in Test 4?",
        timeout=10
    )],
    name=f"Verdrehte Folge",
    points=2
))

success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
