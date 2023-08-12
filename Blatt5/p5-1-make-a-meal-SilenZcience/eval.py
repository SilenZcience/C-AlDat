from testers.outputtests import *
from testers.check_output import extract_order
from testers.menu import *
from testers.target import flatten_targets
import io

def strip_newline(s):
    return s.replace('\r', '').replace('\n','')

class DependencyTest(StatusTest):
    def __init__(self, target, solfile, name="", description="", points="", timeout=1, critical=False):
        super().__init__(
            f"cat {solfile}",
            name=name,
            description=description,
            points=points,
            timeout=timeout,
            critical=critical
        )

        self.target = target
        self.solfile = solfile

    def _award_points(self):
        try:
            with open(self.solfile) as solution:
                sol_text = solution.read()

            output_order = extract_order(sol_text, all_targets)

            t = self.target
            if not t.name in output_order:
                print(f"Ziel {t.name} nicht in Ausgabe gefunden.")
                self.status = Status.WRONG_OUTPUT
                return

            deps_satisfied = True
            for d in t.depends:
                if not d.name in output_order:
                    print(f"Abhängigkeit von {t.name} nicht in Ausgabe gefunden.")
                    deps_satisfied = False
                    self.status = Status.WRONG_OUTPUT
                    return

                if output_order[d.name] == -1:
                    print(f"Abhängigkeit {d.name} von {t.name} mehrfach in Ausgabe gefunden -> nicht gewertet.")
                    self.status = Status.WRONG_OUTPUT
                    return

                if output_order[d.name] >= output_order[t.name]:
                    print(f"Abhängigkeit von {t.name} nicht erfüllt.")
                    deps_satisfied = False
                    self.status = Status.WRONG_OUTPUT
                    return

            if len(t.depends) >= 1:
                print(f"Alle direkten Abhängigkeiten von {t.name} erfüllt und {t.name} ausgeführt (+1P).")
                self.awarded_points = self.total_points

            self.status = Status.SUCCESS

        except IOError:
            print("Konnte Ausgabe von Make nicht lesen, stop.")


all_targets = []
flatten_targets(menu, all_targets)

tests = TestSuite("Aufgabe: Make-a-Meal")
tests.add(StatusTest(
        "make > make.out",
        name="Make Ausführung?",
        description="Kann Make ausgeführt werden?",
        points = 0,
        critical=True
))

tests.add(DependencyTest(
        menu,
        "make.out",
        name="Abhängigkeiten: menu",
        description="Abhängigkeiten von menu erfüllt?",
        points = 1
))

tests.add(DependencyTest(
        vorspeise,
        "make.out",
        name="Abhängigkeiten: vorspeise",
        description="Abhängigkeiten von vorspeise erfüllt?",
        points = 1
))

tests.add(DependencyTest(
        dressing_herstellen,
        "make.out",
        name="Abhängigkeiten: dressing-herstellen",
        description="Abhängigkeiten von dressing-herstellen erfüllt?",
        points = 1
))

tests.add(DependencyTest(
        hauptgericht,
        "make.out",
        name="Abhängigkeiten: hauptgericht",
        description="Abhängigkeiten von hauptgericht erfüllt?",
        points = 1
))

tests.add(DependencyTest(
        kartoffeln_kochen,
        "make.out",
        name="Abhängigkeiten: kartoffeln-kochen",
        description="Abhängigkeiten von kartoffeln-kochen erfüllt?",
        points = 1
))

tests.add(DependencyTest(
        fleisch_zubereiten,
        "make.out",
        name="Abhängigkeiten: fleisch-zubereiten",
        description="Abhängigkeiten von fleisch-zubereiten erfüllt?",
        points = 1
))

tests.add(DependencyTest(
        fleisch_braten,
        "make.out",
        name="Abhängigkeiten: fleisch-anbraten",
        description="Abhängigkeiten von fleisch-anbraten erfüllt?",
        points = 1
))

tests.add(DependencyTest(
        dessert,
        "make.out",
        name="Abhängigkeiten: dessert",
        description="Abhängigkeiten von dessert erfüllt?",
        points = 1
))

tests.add(DependencyTest(
        mit_schoko_garnieren,
        "make.out",
        name="Abhängigkeiten: mit-schoko-garnieren",
        description="Abhängigkeiten von mit-schoko-garnieren erfüllt?",
        points = 1
))

tests.add(DependencyTest(
        gruetze_verteilen,
        "make.out",
        name="Abhängigkeiten: gruetze-verteilen",
        description="Abhängigkeiten von gruetze-verteilen erfüllt?",
        points = 1
))

success = tests.run()
if not success:
    exit(1)
else:
    exit(0)

