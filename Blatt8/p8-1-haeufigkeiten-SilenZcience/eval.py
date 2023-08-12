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

tests = TestSuite("Aufgabe: Haeufigkeiten")

# add further tests here
tests.add(StatusTest(
    "make && test -f wordcount",
    name="Kompilieren+Linken",
    description="Klappt kompilieren/linken?",
    points=0,
    critical=True
))

test_names = [
    "eindeutige Woerter",
    "wiederholte Woerter",
    "wiederholte Woerter, mixed case",
    "Aldatskript"
]


for num in range(1,5):
    test_name = test_names[num-1]
    tests.add(IncrementalTest([
        CompareWithFileTest(
            rf"./wordcount < testcases/test{num}.in | sort -d",
            rf"testcases/test{num}.out",
            name=f"Test {num}: {test_name}, ohne Sortierung",
            description="",
            points=1,
            timeout=10
        ),
        ValgrindTest(
            rf"./wordcount < testcases/test{num}.in",
            name="Speicherfehler in Test 1?",
            timeout=10
        )],
        name=f"Test {num}: {test_name}",
        points=2
    ))

    tests.add(CompareWithFileTest(
            rf"./wordcount < testcases/test{num}.in",
            rf"testcases/test{num}.out",
            name=f"Test {num}: Sortierung?",
            description="",
            points=1,
            timeout=10
    ))


success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
