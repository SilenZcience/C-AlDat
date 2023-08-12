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

tests = TestSuite("Aufgabe: Labyrinth")

# add further tests here
tests.add(StatusTest(
    "make && test -f pathfinder",
    name="Kompilieren+Linken des Baumes",
    description="Klappt kompilieren/linken?",
    points=0,
    critical=True
))

test_names = [
    "Geradeaus",
    "Rückwärts",
    "Abwärts",
    "Aufwärts",
    "Hoch-Runter-Links-Rechts",
    "Ziel nicht erreichbar",
    "Mehrere Wege: Quadrat",
    "Mehrere Wege: Links-oder-Rechts",
    "Mehrere Wege: Schlange",
    "Mehrere Wege: Irrweg"
]

for idx, t_name in enumerate(test_names):
    tests.add(
        CombinedTest([
            CompareWithFileTest(
                rf"./pathfinder < testcases/test{idx+1}.in",
                rf"testcases/test{idx+1}.out",
                name=t_name,
                description="",
                timeout=60
            ),
            ValgrindTest(
                rf"./pathfinder < testcases/test{idx+1}.in",
                name=f"{t_name}: Speicherfehler?",
                timeout=60
            )
        ],
        name=t_name,
        points=1
    ))

success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
