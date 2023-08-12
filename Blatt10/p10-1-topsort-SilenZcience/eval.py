from testers.outputtests import *
import io
import re
import argparse

# In welcher Zeile wird welcher Knoten ausgegeben?
def extract_order(user_output, node_set):
    lines = io.StringIO(user_output)

    order = dict()
    for idx, line in enumerate(lines):
        try:
            node = int(line)
        except:
            print(f"Zeile '{line.strip()}' ist keine gültige Ausgabe")
            return None

        if not node in node_set:
            print(f"Knoten {node} ist kein gültiger Knoten.")
            return None

        if node in order:
            print(f"Knoten {node} kommt mehrfach in der Ausgabe vor.")
            return None

        order[node] = idx

    return order


def compare_partial_order(user_output, order_file_name):
    edges = []
    with open(order_file_name, "r") as order_file:
        n_nodes = int(order_file.readline()) # skip n_nodes
        nodes = range(n_nodes)
        for line in order_file:
            if line.strip() == "":
                continue

            e = [ int(t) for t in line.split() ]
            edges.append(e)

    user_order = extract_order(user_output, nodes)
    if not user_order:
        print("Benutzerausgabe ist fehlerhaft.")
        return False

    for e in edges:
        if e[0] not in user_order:
            print(f"Knoten {e[0]} fehlt in der Ausgabe.")
            return False

        if e[1] not in user_order:
            print(f"Knoten {e[1]} fehlt in der Ausgabe.")
            return False

        if user_order[e[0]] > user_order[e[1]]:
            print(f"Kante von {e[0]} nach {e[1]}, aber {e[0]} in Sortierung nach {e[1]}.")
            return False

    for i in nodes:
        if not i in user_order:
            print(f"(Isolierter) Knoten {i} fehlt in der Ausgabe.")
            return False

    return True

def match_content(user_output, test_out_filename):
    with open(test_out_filename, "r") as test_out:
        expected_output = test_out.read()

    return user_output.strip() == expected_output.strip()


class IncrementalTest(CombinedTest):
    def __init__(self, tests, name="", description="", points=1, critical=False):
        super().__init__(tests, name, description, points, critical)

    def _award_points(self):
        self.awarded_points = 0
        for t in self.tests:
            if t.status != Status.SUCCESS:
                return

        self.awarded_points = self.total_points

tests = TestSuite("Aufgabe: Topsort")

# add further tests here
tests.add(StatusTest(
    "make && test -f topsort",
    name="Kompilieren+Linken",
    description="Klappt kompilieren/linken?",
    points=0,
    critical=True
))

test_names = [
    "Weg (klein)",
    "Weg (groß)",
    "Weg mit mehr Zufall (klein)",
    "Weg mit mehr Zufall (groß)",
    "Kreis (klein)",
    "Kreis mit mehr Zufall (groß)",
    "Graphen ohne Kanten (klein)",
    "Graphen ohne Kanten (groß)",
    "Viele Wege (klein)",
    "Viele Wege (groß)",
]

# Ohne Speicher überprüfung, kleine Tests

i = 1
tests.add(CompareOutputTest(
    rf"./topsort < testcases/test{i}.in",
    rf"testcases/test{i}.in",
    comparer=compare_partial_order,
    name=f"{test_names[i-1]}",
    description=f"Ein Weg.",
    points=1
))

i = 3
tests.add(CompareOutputTest(
    rf"./topsort < testcases/test{i}.in",
    rf"testcases/test{i}.in",
    comparer=compare_partial_order,
    name=f"{test_names[i-1]}",
    description=f"Ein Weg, der nicht sortiert gegeben ist.",
    points=1
))


i = 5
tests.add(CompareOutputTest(
    rf"./topsort < testcases/test{i}.in",
    rf"testcases/test{i}.out",
    comparer=match_content,
    name=f"{test_names[i-1]}",
    description=f"Ein Kreis.",
    points=1
))

i = 7
tests.add(CompareOutputTest(
    rf"./topsort < testcases/test{i}.in",
    rf"testcases/test{i}.in",
    comparer=compare_partial_order,
    name=f"{test_names[i-1]}",
    description=f"Graph ohne Kanten.",
    points=1
))

i = 9
tests.add(CompareOutputTest(
    rf"./topsort < testcases/test{i}.in",
    rf"testcases/test{i}.in",
    comparer=compare_partial_order,
    name=f"{test_names[i-1]}",
    description=f"Graph mit mehreren Wegen in verschiedenen Zusammenhangskomponenten",
    points=1
))

# Größere Testfälle mit Speicherüberprüfung

i = 2
tests.add(
    IncrementalTest([
        CompareOutputTest(
            rf"./topsort < testcases/test{i}.in",
            rf"testcases/test{i}.in",
            name=f"{test_names[i-1]}",
            comparer=compare_partial_order,
            description="Ein längerer Weg",
            timeout=10
        ),
        ValgrindTest(
            rf"./topsort < testcases/test{i}.in",
            name=f"{test_names[i-1]}: Speicherfehler?",
            timeout=10
        )
    ],
    name=f"{test_names[i-1]}",
    points=1
))

i = 4
tests.add(
    IncrementalTest([
        CompareOutputTest(
            rf"./topsort < testcases/test{i}.in",
            rf"testcases/test{i}.in",
            name=f"{test_names[i-1]}",
            comparer=compare_partial_order,
            description="Ein längerer unsortierter Weg",
            timeout=10
        ),
        ValgrindTest(
            rf"./topsort < testcases/test{i}.in",
            name=f"{test_names[i-1]}: Speicherfehler?",
            timeout=10
        )
    ],
    name=f"{test_names[i-1]}",
    points=1
))

i = 6
tests.add(
    IncrementalTest([
        CompareOutputTest(
            rf"./topsort < testcases/test{i}.in",
            rf"testcases/test{i}.out",
            name=f"{test_names[i-1]}",
            comparer=match_content,
            description="Ein größerer Kreis",
            timeout=10
        ),
        ValgrindTest(
            rf"./topsort < testcases/test{i}.in",
            name=f"{test_names[i-1]}: Speicherfehler?",
            timeout=10
        )
    ],
    name=f"{test_names[i-1]}",
    points=1
))

i = 8
tests.add(
    IncrementalTest([
        CompareOutputTest(
            rf"./topsort < testcases/test{i}.in",
            rf"testcases/test{i}.in",
            name=f"{test_names[i-1]}",
            comparer=compare_partial_order,
            description="Ein Graph mit vielen knoten aber ohne Kanten",
            timeout=10
        ),
        ValgrindTest(
            rf"./topsort < testcases/test{i}.in",
            name=f"{test_names[i-1]}: Speicherfehler?",
            timeout=10
        )
    ],
    name=f"{test_names[i-1]}",
    points=1
))

i = 10
tests.add(
    IncrementalTest([
        CompareOutputTest(
            rf"./topsort < testcases/test{i}.in",
            rf"testcases/test{i}.in",
            name=f"{test_names[i-1]}",
            comparer=compare_partial_order,
            description="VieleWege in mehreren zusammenhangskomponenten.",
            timeout=10
        ),
        ValgrindTest(
            rf"./topsort < testcases/test{i}.in",
            name=f"{test_names[i-1]}: Speicherfehler?",
            timeout=10
        )
    ],
    name=f"{test_names[i-1]}",
    points=1
))


success = tests.run()
if not success:
    exit(1)
else:
    exit(0)
