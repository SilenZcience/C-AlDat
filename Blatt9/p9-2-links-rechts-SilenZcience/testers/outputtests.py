import subprocess
import re
import math
import time
import os
import platform
import signal

from subprocess import Popen, TimeoutExpired
from enum import Enum

class Status(Enum):
    SUCCESS="SUCCESS"
    ERROR="ERROR"
    TIMEOUT="TIMEOUT"
    WRONG_OUTPUT="WRONG_OUTPUT"
    UNKNOWN="UNKNOWN"
    RUNTIME_ERROR="RUNTIME_ERROR"
    VALGRIND_ERROR="MEMORY_ERROR"

class StatusTest:
    def __init__(self, cmd, name="", description="", points=1, timeout=1, critical=False):
        self.cmd = cmd
        self.name = name
        self.description = description
        self.timeout = timeout
        self.total_points = points
        self.critical=critical

        self.wall_time = 0

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
        start_time = time.time_ns()
        p = Popen(
            self._build_command(),
            shell=True,
            stdout=self._out_stream,
            stderr=self._err_stream,
            start_new_session=True
        )

        try:
            self.std_output, self.err_output = p.communicate(timeout=self.timeout)
            self._process_returncode(p)
        
        except TimeoutExpired:
            if platform.system() == "Windows":
                print("Warnung: Kann unter Windows Kindprozesse nicht beenden.")
                print("Bitte beenden Sie ggf. weiterlaufende Prozesse im Taskmanager")
            self.status = Status.TIMEOUT

        finally:
            try:
                # kill process and all child processes
                # does not work on windows!
                os.killpg(p.pid, signal.SIGKILL)
            except OSError:
                pass

            # only kills shell, not subprocesses of shell
            p.terminate()
            p.kill()


        self.wall_time = time.time_ns() - start_time

    
    def run(self):
        print()
        print(f"[Test] {self.name}: {self.description}")
        print(f"-- Befehl: {self._build_command()}")
        print("-- Ausgabe -----------------------------------------------------------")
        self._call_test_command()
        self._award_points()
        print("----------------------------------------------------------------------")
        print(f"Ergebnis: {self.status.value} | Zeit: {float(self.wall_time)/1e9:5.2f}s | Punkte: {self.awarded_points} von {self.total_points}")
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
        return f"{cmd} | diff -y -b -B -Z --strip-trailing-cr -s --suppress-common-lines {outfile} -"

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

def match_re(actual, expected_re):
    print(f"Benutzerausgabe: '{actual.strip()}'")
    if re.match(expected_re, actual):
        return True

    return False


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

        if not self.comparer(self.std_output.decode("utf-8"), self.expected_output):
            self.status = Status.WRONG_OUTPUT
            self.awarded_points = 0
        else:
            self.status = Status.SUCCESS
            self.awarded_points = self.total_points


class RuntimeErrorTest(StatusTest):
    def __init__(self, cmd, name="", description="", points=1, timeout=1):
        super().__init__(
            cmd, 
            name=name, 
            description=description, 
            points=points, 
            timeout=timeout
        )
        self._err_stream = subprocess.PIPE 
        self._out_stream = subprocess.PIPE 

    def _award_points(self):

        if self.status == Status.TIMEOUT or self.status == Status.ERROR:
            self.awarded_points = 0
            return

        if "runtime error" in self.err_output.decode("utf-8"):
            print(f"{self.err_output.decode('utf-8')}")
            self.status = Status.RUNTIME_ERROR
            self.awarded_points = 0
        else:
            self.status = Status.SUCCESS
            self.awarded_points = self.total_points


class CompareWithFileContentTest(CompareOutputTest):
    @staticmethod
    def _read_file_content(filename):
        with open(filename) as infile:
            return infile.read()

    def __init__(self, cmd, expected_file, comparer=match_exact, name="", description="", points=1, timeout=1):
        super().__init__(
            cmd,
            self._read_file_content(expected_file),
            comparer,
            name,
            description,
            points,
            timeout
        )

# 2>&1 valgrind --log-file=valgrind_eingabe_$X_$Y.log ./bruecken g_$X.txt g_$Y.txt test_out_muell.txt  > /dev/null 

class ValgrindTest(StatusTest):

    def __init__(self, cmd, name="", description="", points=1, timeout=1, logfile="valgrind.log"):
        valgrind_cmd = f"valgrind --leak-check=full --track-origins=yes --error-exitcode=2 --log-file={logfile} {cmd} > /dev/null"
        super().__init__(
            valgrind_cmd,
            name,
            description,
            points,
            timeout,
        )
        self.logfile = logfile

    def _award_points(self):
        error_res = [
            r"Invalid read",
            r"Invalid write",
            r"Conditional jump or move depends on uninitialised value",
            r"Use of uninitialised value",
            r"Access not within mapped region",
            r"(\d+) bytes .* definitely lost"
        ]
        
        if self.status == Status.TIMEOUT:
            self.awarded_points = 0
            return

        if self.status == Status.ERROR:
            print(f"----------------------------------------------------------------------")
            print(f"Valgrind wurde mit dem Befehl")
            print(f"\t{self.cmd}")
            print(f"aufgerufen.")
            print(f"")
            print(f"Führen Sie den Befehl lokal aus und beheben Sie die Fehler!")
            print(f"Valgrind Ausgabe:")
            print(f"----------------------------------------------------------------------")
            self.awarded_points = 0
            with open(self.logfile) as valgrind_log:
                for line in valgrind_log:
                    print(line.strip())
                    for error in error_res:
                        if re.search(error, line):
                            self.status = Status.VALGRIND_ERROR
        else:
            self.status = Status.SUCCESS
            self.awarded_points = self.total_points
        

class OutputSubSetTest(StatusTest):
    def __init__(self, cmd, from_file, name="", description="", points=1, timeout=5):
        super().__init__(
            cmd,
            name=name,
            description=description,
            points=points,
            timeout=timeout
        )
        self.from_file = from_file

        self._err_stream=subprocess.STDOUT
        self._out_stream=subprocess.PIPE


    def _award_points(self):
        if self.status == Status.TIMEOUT or self.status == Status.ERROR:
            self.awarded_points = 0
            return

        with open(self.from_file) as exp_output_file:
            expected_output = { int(x) for x in exp_output_file.read().split() }

        try:
            usr_output = [int(x) for x in self.std_output.decode("UTF-8").split()]
            for x in usr_output:
                if not x in expected_output:
                    print(f"Zahl {x} nicht in Ausgabe erwartet.")
                    self.awarded_points = 0
                    self.status = Status.WRONG_OUTPUT
                    return

            self.awarded_points = self.total_points
            self.status = Status.SUCCESS


        except ValueError:
            print("Ausgabe enthält unzulässige Zeichen.")
            self.awarded_points = 0
            self.status = Status.WRONG_OUTPUT


class OutputSuperSetTest(StatusTest):
    def __init__(self, cmd, from_file, name="", description="", points=1, timeout=5):
        super().__init__(
            cmd,
            name=name,
            description=description,
            points=points,
            timeout=timeout
        )
        self.from_file = from_file

        self._err_stream=subprocess.STDOUT
        self._out_stream=subprocess.PIPE


    def _award_points(self):
        if self.status == Status.TIMEOUT or self.status == Status.ERROR:
            self.awarded_points = 0
            return

        with open(self.from_file) as exp_output_file:
            expected_output =  [int(x) for x in exp_output_file.read().split()]

        try:
            usr_output = { int(x) for x in self.std_output.decode("UTF-8").split() }
            for x in expected_output:
                if not x in usr_output:
                    print(f"Zahl {x} fehlt in der Ausgabe.")
                    self.awarded_points = 0
                    self.status = Status.WRONG_OUTPUT
                    return

            self.awarded_points = self.total_points
            self.status = Status.SUCCESS


        except ValueError:
            print("Ausgabe enthält unzulässige Zeichen.")
            self.awarded_points = 0
            self.status = Status.WRONG_OUTPUT

class IsSortedTest(StatusTest):
    def __init__(self, cmd, name="", description="", points=1, timeout=5):
        super().__init__(
            cmd,
            name=name,
            description=description,
            points=points,
            timeout=timeout
        )

        self._err_stream=subprocess.STDOUT
        self._out_stream=subprocess.PIPE

    @staticmethod
    def _is_sorted(l):
        for i,j in zip(l, l[1:]):
            if i > j:
                return False

        return True

    def _award_points(self):
        if self.status == Status.TIMEOUT or self.status == Status.ERROR:
            self.awarded_points = 0
            return

        try:
            usr_output = [int(x) for x in self.std_output.decode("UTF-8").split()]

            if not self._is_sorted(usr_output):
                print(f"Ausgabe ist nicht sortiert.")
                self.awarded_points = 0
                self.status = Status.WRONG_OUTPUT

            self.awarded_points = self.total_points
            self.status = Status.SUCCESS

        except ValueError:
            print("Ausgabe enthält unzulässige Zeichen.")
            self.awarded_points = 0
            self.status = Status.WRONG_OUTPUT

class CombinedTest:
    def __init__(self, tests, name="", description="", points=1, critical=False):
        self.name=name
        self.description=description
        self.tests = tests
        self.status = Status.ERROR
        self.awarded_points = 0
        self.total_points = points
        self.critical = critical
        self.wall_time = 0

    def run(self):
        print(f"[Kombinierter Test]: {self.name}")
        print(f"+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+")
        for t in self.tests:
            t.run()
            self.wall_time += t.wall_time

        self._process_status()
        self._award_points()
        print(f"+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+")
        print(f"Ergebnis des kombinierten Tests: {self.status.value} | {self.awarded_points} von {self.total_points} Punkten")
        print()

    def _process_status(self):
        self.status = Status.SUCCESS
        for t in self.tests:
            if t.status != Status.SUCCESS:
                self.status = t.status
                return

    def _award_points(self):
        if self.status == Status.SUCCESS:
            self.awarded_points = self.total_points
        else:
            self.awarded_points = 0

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
            if t.critical and t.status != Status.SUCCESS:
                print("Kritischer Test fehlgeschlagen; breche Testlauf ab...")
                break

        total_points = 0
        for t in self.test_cases:
            total_points += t.total_points

        awarded_points = 0
        success = True
        max_label_len = max([len(t.name) for t in self.test_cases])
        print()
        print("== ZUSAMMENFASSUNG ===================================================")
        print(f"Testlauf | {self.name}")
        for t in self.test_cases:
            awarded_points += t.awarded_points
            if t.status != Status.SUCCESS:
                success = False
            print(f"  {t.name:{max_label_len}}   [{t.status.value:12}]    [time: {float(t.wall_time)/1e9:5.2f}s] | {t.awarded_points} von {t.total_points} Punkt(en)")

        print()
        print(f"Erreichte Punkte: {math.ceil(awarded_points)}")
        print(f"Gesamtpunkte: {total_points}")
        print("== ENDE des Testlaufs ================================================")

        return success
