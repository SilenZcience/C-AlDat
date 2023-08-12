import subprocess
from subprocess import Popen, TimeoutExpired
from enum import Enum

class Status(Enum):
    SUCCESS="SUCCESS"
    ERROR="ERROR"
    TIMEOUT="TIMEOUT"
    WRONG_OUTPUT="WRONG_OUTPUT"
    UNKNOWN="UNKNOWN"

class StatusTest:
    def __init__(self, cmd, name="", description="", points=1, timeout=1):
        self.cmd = cmd
        self.name = name
        self.description = description
        self.timeout = timeout
        self.total_points = points

        self.status = Status.UNKNOWN
        self.awarded_points = 0
        self._out_stream = None
        self._err_stream = None

    def _build_command(self):
        return self.cmd

    def _process_returncode(self, p):    
        if p.returncode == 0:
            self.status = Status.SUCCESS
        elif p.returncode == 1:
            self.status = Status.WRONG_OUTPUT
        else:
            self.status = Status.ERROR

    def _award_points(self):
        if self.status == Status.SUCCESS:
            self.awarded_points = self.total_points
        else:
            self.awarded_points = 0

    def _call_test_command(self):
        try:
            p = Popen(
                self._build_command(), 
                shell=True, 
                stdout=self._out_stream, 
                stderr=self._err_stream
            )

            self.std_output, self.err_output = p.communicate(self.timeout)
            self._process_returncode(p)
        
        except TimeoutExpired:
            p.kill()
            self.status = Status.TIMEOUT
    
    def run(self):
        print()
        print(f"[Test] {self.name}: {self.description}")
        print("-- Ausgabe -----------------------------------------------------------")
        self._call_test_command()
        self._award_points()
        print("----------------------------------------------------------------------")
        print(f"Ergebnis: {self.status.value} |  Punkte: {self.awarded_points} von {self.total_points}")
        print()
        pass

class CompilerTest(StatusTest):
    def _build_compile_command(self, source_file, outfile, flags):
        return f"""gcc {" ".join(flags)} -o {outfile} {source_file}"""
    
    def __init__(self, source_file, outfile, flags=["-Wall", "-O2", "-DNDEBUG"], name="", description="", points=1, timeout=5):
        super().__init__(
            self._build_compile_command(source_file, outfile, flags),
            name=name,
            description=description,
            points=points,
            timeout=timeout
        )

class CompareWithFileTest(StatusTest):
    @staticmethod
    def _build_diff_command(cmd, outfile):
        return f"{cmd} | diff -u -s {outfile} -"

    def __init__(self, cmd, match_file, name="", description="", points=1, timeout=1):
        super().__init__(
            self._build_diff_command(cmd, match_file), 
            name=name,
            description=description,
            points=points,
            timeout=timeout
        )


class FindPatternTest(StatusTest):
    @staticmethod
    def _build_grep_command(cmd, pattern):
        return f"{cmd} 2>&1 | grep '{pattern}'"


    def __init__(self, cmd, pattern, name="", description="", points=1, timeout=1):
        super().__init__(
            self._build_grep_command(cmd, pattern), 
            name=name,
            description=description,
            points=points,
            timeout=timeout
        )


def match_exact(actual, expected):
    return actual == expected

def match_int(actual, expected):
    return int(actual) == expected

def match_float(actual, expected):
    return abs(float(actual) - expected) < 0.0001

def match_exact_array(actual, expected):
    for a, e in zip(actual.split(), expected):
        if not match_exact(a, e):
            return False 
    
    return True

def match_int_array(actual, expected):
    for a, e in zip(actual.split(), expected):
        if not match_int(a, e):
            return False
    
    return True

def match_float_array(actual, expected):
    for a, e in zip(actual.split(), expected):
        if not match_float(a, e):
            return False
    
    return True

class CompareOutputTest(StatusTest):
    def __init__(self, cmd, expected_output, comparer=match_exact, name="", description="", points=1, timeout=1):
        super().__init__(
            cmd, 
            name=name, 
            description=description, 
            points=points, 
            timeout=timeout
        )
        self.comparer = comparer
        self.expected_output = expected_output
        self._err_stream=subprocess.STDOUT 
        self._out_stream=subprocess.PIPE

    def _award_points(self):
        if self.status == Status.TIMEOUT or self.status == Status.ERROR:
            self.awarded_points = 0
            return

        if self.comparer(self.output, self.expected_output):
            self.awarded_points = 0
        else:
            self.awarded_points = self.total_points



class TestSuite:
    def __init__(self, name=""):
        self.name=name
        self.test_cases = []

    def add(self, testcase):
        self.test_cases.append(testcase)

    def run(self):
        print(f"Starte Testlauf für {self.name}")
        for t in self.test_cases:
            t.run()
        
        total_points = 0
        awarded_points = 0
        success = True
        print()
        print("== ZUSAMMENFASSUNG ===================================================")
        print(f"Testlauf | {self.name}")
        for t in self.test_cases:
            total_points += t.total_points
            awarded_points += t.awarded_points
            if t.status != Status.SUCCESS:
                success = False
            print(f"  {t.name:25}   [{t.status.value:12}]  | {t.awarded_points} von {t.total_points} Punkt(en)")

        print()
        print(f"Erreichte Punkte: {awarded_points}")
        print(f"Gesamtpunkte: {total_points}")
        print("== ENDE des Testlaufs ================================================")

        return success
