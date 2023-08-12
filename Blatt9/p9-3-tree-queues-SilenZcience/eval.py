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

tests = TestSuite("Aufgabe: Tree Queues")

# add further tests here
tests.add(StatusTest(
    "make treetest && test -f treetest",
    name="Kompilieren+Linken des Baumes",
    description="Klappt kompilieren/linken?",
    points=0,
    critical=True
))

tests.add(StatusTest(
    "make pqtest && test -f pqtest",
    name="Kompilieren+Linken",
    description="Klappt kompilieren/linken?",
    points=0,
    critical=False
))

tests.add(
    CombinedTest([
        CompareWithFileTest(
            rf"./treetest m < testcases/tree.in",
            rf"testcases/tree1.out",
            name="Baum: Methode minimum",
            description="",
            timeout=10
        ),
        ValgrindTest(
            rf"./treetest m < testcases/tree.in",
            name="Speicherfehler?",
            timeout=10
        )
    ],
    name="Methode Minimum",
    points=1
))

tests.add(
    CombinedTest([
        CompareWithFileTest(
            rf"./treetest M < testcases/tree.in",
            rf"testcases/tree2.out",
            name="Baum: Methode maximum",
            description="",
            timeout=10
        ),
        ValgrindTest(
            rf"./treetest M < testcases/tree.in",
            name="Speicherfehler?",
            timeout=10
        )
    ],
    name="Methode Maximum",
    points=1
))

test_names = [
    "Methode insert",
    "Methode extract-min",
    "Methode extract-max",
    "Methode update",
    "Gemischte Eingabe"
]

for idx, t_name in enumerate(test_names):
    tests.add(
        CombinedTest([
            CompareWithFileTest(
                rf"./pqtest < testcases/test{idx+1}.in",
                rf"testcases/test{idx+1}.out",
                name=t_name,
                description="",
                timeout=10
            ),
            ValgrindTest(
                rf"./pqtest < testcases/test{idx+1}.in",
                name=f"{t_name}: Speicherfehler?",
                timeout=10
            )
        ],
        name=t_name,
        points=1
    ))

for num in range(1,4):
    tests.add(StatusTest(
        rf"sha1sum -c testcases/sol{num}.sha",
        name=f"Frage {num}?",
        description=f"Frage {num} richtig beantwortet?"
    ))

success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
