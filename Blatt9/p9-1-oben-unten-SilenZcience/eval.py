from testers.outputtests import *
import io
import re
import argparse

class IncrementalTest(CombinedTest):
    def __init__(self, tests, name="", description="", points=1, critical=False):
        super().__init__(tests, name, description, points, critical)

    def _award_points(self):
        self.awarded_points = 0
        for t in self.tests:
            if t.status != Status.SUCCESS:
                break

            self.awarded_points += t.awarded_points

tests = TestSuite("Aufgabe: Oben-Unten")

# add further tests here
tests.add(StatusTest(
    "make && test -f levels",
    name="Kompilieren+Linken des Baumes",
    description="Klappt kompilieren/linken?",
    points=0,
    critical=True
))

test_names = [
    "Mini-Baum",
    "vollständiger Baum",
    "unvollständiger Baum",
    "unbalancierter Baum"
]

for idx, t_name in enumerate(test_names):
    tests.add(
        IncrementalTest([
            CompareWithFileTest(
                rf"./levels < testcases/test{idx+1}.in",
                rf"testcases/test{idx+1}.out",
                name=t_name,
                description="",
                timeout=10
            ),
            ValgrindTest(
                rf"./levels < testcases/test{idx+1}.in",
                name=f"{t_name}: Speicherfehler?",
                timeout=10
            )
        ],
        name=t_name,
        points=2
    ))

tests.add(StatusTest(
    rf"sha1sum -c testcases/sol.sha",
    name=f"Frage?",
    description=f"Optimale Datenstruktur gewählt?",
    points=2
))


success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
