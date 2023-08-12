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


arg_parser = argparse.ArgumentParser("Testsuite fuer links-rechts")
arg_parser.add_argument("--pdf", help="Rufe graphviz/dot auf, um die Ausgabe in einem PDF zu layouten.", action="store_true")
args = arg_parser.parse_args();

tests = TestSuite("Aufgabe: Links-Rechts")

# add further tests here
tests.add(StatusTest(
    "make treetest && test -f treetest",
    name="Kompilieren+Linken des Baumes",
    description="Klappt kompilieren/linken?",
    points=0,
    critical=True
))

test_names = [
    "Einfache Rechtsrotation",
    "Einfache Linksrotation",
    "Komplexe Rechtsrotation",
    "Rechtsrotation mit Elternknoten",
    "Mehrfache Rotationen"
]

for idx, t_name in enumerate(test_names):
    tests.add(
        IncrementalTest([
            CompareWithFileTest(
                rf"./treetest < testcases/test{idx+1}.in",
                rf"testcases/test{idx+1}.dot",
                name=t_name,
                description="",
                timeout=10
            ),
            ValgrindTest(
                rf"./treetest < testcases/test{idx+1}.in",
                name=f"{t_name}: Speicherfehler?",
                timeout=10
            )
        ],
        name=t_name,
        points=2
    ))

if args.pdf:
    tests.add(
        CombinedTest([
            StatusTest(
                f"dot -O -Tpdf testcases/test{idx+1}.dot",
                name=f"Erzeuge pdf für Testfall {idx+1}...",
                points=0,
                critical=False
            )
            for idx in range(len(test_names))
        ],
        name="Erzeuge pdfs",
        points=0
    ))


success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
