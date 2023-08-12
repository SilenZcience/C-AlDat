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

tests = TestSuite("Aufgabe: Eiswagen")

# add further tests here
tests.add(StatusTest(
    "make && test -f eiswagen",
    name="Kompilieren+Linken",
    description="Klappt kompilieren/linken?",
    points=0,
    critical=True
))

test_names = [
    "Nur Kreuzungen",
    "Sortierte Straßen",
    "Nicht sortierte Straßen",
    "Erst hinzufügen, dann entfernen",
    "Gesmischte Operationen"
]


for num in range(1,6):
    test_name = test_names[num-1]
    tests.add(IncrementalTest([
        CompareWithFileTest(
            rf"./eiswagen < testcases/test{num}.in ",
            rf"testcases/test{num}.out",
            name=f"Test {num}: {test_name}, ohne Sortierung",
            description="",
            points=1,
            timeout=10
        ),
        ValgrindTest(
            rf"./eiswagen < testcases/test{num}.in",
            name=f"Speicherfehler in Test {num}?",
            timeout=10
        )],
        name=f"Test {num}: {test_name}",
        points=2
    ))


success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
