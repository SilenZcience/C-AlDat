from testers.outputtests import *
import io
import re
import argparse


class TimedTest(StatusTest):
    def __init__(self, cmd, name="", description="", points=1, mintime_ms=0, maxtime_ms=1, timeout=1, critical=False, repetitions=1):
        super().__init__(cmd, name=name, description=description, points=points, timeout=timeout, critical=critical)
        self.mintime_ms=mintime_ms
        self.maxtime_ms=maxtime_ms
        self.repetitions=repetitions


    def _award_points(self):
        #print(f"Zeit: Wall {self.wall_time:,} ns | Min {self.mintime_ms*1e6:,} | Max {self.maxtime_ms*1e6:,}")
        if self.status == Status.SUCCESS:
            if self.wall_time < self.mintime_ms*1e6:
                print("Der Algorithmus war zu schnell!")

                self.status = Status.TIMELIMIT
                self.awarded_points = 0

            elif self.wall_time > self.maxtime_ms*1e6:
                print("Der Algorithmus war zu langsam!")

                self.status = Status.TIMELIMIT
                self.awarded_points = 0

            else:
                self.awarded_points = self.total_points
        else:
            self.awarded_points = 0


    def run(self):
        print()
        print(f"[Test] {self.name}: {self.description}")
        print("-- Ausgabe -----------------------------------------------------------")
        times = []
        status = []
        for i in range(0, self.repetitions):
            self._call_test_command()
            times.append(self.wall_time)
            status.append(self.status)
        self.wall_time = sum(times)/len(times)

        if status.count(Status.SUCCESS) > self.repetitions/2:
            # majority was successful
            self.status = Status.SUCCESS
        else:
            # majority failed, why?
            if status.count(Status.UNKNOWN) > 0:
                self.status = Status.UNKNOWN

            elif status.count(Status.ERROR) > 0:
                self.status = Status.ERROR

            elif status.count(RUNTIME_ERROR) > 0:
                self.status = Status.RUNTIME_ERROR

            elif status.count(MEMORY_ERROR) > 0:
                self.status = Status.MEMORY_ERROR

            elif status.count(Status.WRONG_OUTPUT) > 0:
                self.status = Status.WRONG_OUTPUT

            elif status.count(Status.TIMEOUT) > status.count(Status.TIMELIMIT):
                self.status = Status.TIMEOUT

            else:
                self.status = Status.TIMELIMIT

        self._award_points()
        print("----------------------------------------------------------------------")
        if self.repetitions > 1:
            print(f"Es wurden {self.repetitions} Durchläufe durchgeführt. Die Durchschnitlichen Ergebnisse lauten:")
            print("----------------------------------------------------------------------")
        print(f"Ergebnis: {self.status.value} | Zeit: {float(self.wall_time)/1e6:5.0f}ms | Punkte: {self.awarded_points} von {self.total_points}")
        print()
        pass

def benchmark():
    print("Fuehre Benchmark durch, bitte warten...")
    start_time = time.time_ns()
    p = Popen(
        "./sortme s < benchmark.in",
        shell=True
    )
    p.communicate()
    end_time = time.time_ns()
    total_time_ms = float(end_time - start_time) / 10e6
    server_time = 380
    speed_factor = total_time_ms / server_time
    print(f"### Zeit fuer Benchmark: {total_time_ms:.0f}ms | Geschwindigkeitsfaktor: {speed_factor:.2f} ###")


def main():
    exercise = "Sortieralgorithmen"
    parser = argparse.ArgumentParser(description=f"Testskript für Aufgabe {exercise}")
    parser.add_argument('--repetitions', type=int, default=1,
                        help="Auf dem Server möchten wir die Zeitmessungen wiederholen")
    args = parser.parse_args()
    
    
    tests = TestSuite(f"Aufgabe: {exercise}")

    # add further tests here
    tests.add(StatusTest(
        "make && test -f sortme",
        name="Kompilieren+Linken",
        description="Klappt kompilieren/linken?",
        points=0,
        critical=True,
    ))

    algo_names = {
     'i': "InsertionSort",
     'q': "QuickSort",
     'm': "MergeSort",
     's': "SelectionSort"
    }

    timeout=5
    ulimit=10

    inputs = [
        {
            "file": "testcases/insertionsort1.in",
            "algo": "i",
            "size": 1000000,
            "mintime": 0,
            "maxtime": 150,
            "points": 1
        },
        {
            "file": "testcases/insertionsort2.in",
            "algo": "i",
            "size": 100000,
            "mintime": 2500,
            "maxtime": 3500,
            "points": 1
        },
        {
            "file": "testcases/selectionsort1.in",
            "algo": "s",
            "size": "",
            "mintime": 800,
            "maxtime": 1200,
            "points": 1
        },
        {
            "file": "testcases/selectionsort2.in",
            "algo": "s",
            "size": "",
            "mintime": 2000,
            "maxtime": 3000,
            "points": 1
        },
        {
            "file": "testcases/mergesort1.in",
            "algo": "m",
            "size": 1000000,
            "mintime": 210,
            "maxtime": 500,
            "points": 1
        },
        {
            "file": "testcases/mergesort2.in",
            "algo": "m",
            "size": 1000000,
            "mintime": 0,
            "maxtime": 190,
            "points": 1
        },
        {
            "file": "testcases/quicksort1.in",
            "algo": "q",
            "size": 75000,
            "mintime": 1000,
            "maxtime": 2000,
            "points": 1
        },
        {
            "file": "testcases/quicksort2.in",
            "algo": "q",
            "size": 1000000,
            "mintime": 0,
            "maxtime": 400,
            "points": 1
        }
    ]

    for num, case in enumerate(inputs):
        tests.add(TimedTest(
            rf"ulimit -t {ulimit} && ./sortme {case['algo']} {case['size']} < {case['file']} > /dev/null",
            name=f"{algo_names[case['algo']]:13} | n: {case['size']:7} in {case['mintime']}-{case['maxtime']} ms.",
            description="",
            mintime_ms=case['mintime'],
            maxtime_ms=case['maxtime'],
            points=case['points'],
            timeout=case['maxtime'],
            repetitions=args.repetitions,
        ))

    success = tests.run()

    benchmark()

    if not success:
        exit(1)
    else:
        exit(0)

if __name__ == '__main__':
    main()

