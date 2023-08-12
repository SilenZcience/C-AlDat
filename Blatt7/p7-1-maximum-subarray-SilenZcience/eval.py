from testers.outputtests import *
import io
import re

tests = TestSuite("Aufgabe: Max-Subarray")

# add further tests here
tests.add(StatusTest(
    "make && test -f msa",
    name="Kompilieren+Linken",
    description="Klappt kompilieren/linken?",
    points=0,
    critical=True
))

timeout=2
ulimit=10
inputs = [
    {
        "seed": 4711,
        "size": 500,
        "output": 18420
    },
    {
        "seed": 4712,
        "size": 1000,
        "output": 21105
    },
    {
        "seed": 4713,
        "size": 10000,
        "output": 43558
    },
    {
        "seed": 4714,
        "size": 50000,
        "output": 128011
    },
    {
        "seed": 4715,
        "size": 100000,
        "output": 419863
    },
    {
        "seed": 4716,
        "size": 1000000,
        "output": 1415268
    },
    {
        "seed": 4717,
        "size": 10000000,
        "output": 1971154
    }
]

for num, case in enumerate(inputs):
    tests.add(CompareOutputTest(
        rf"ulimit -t {ulimit} && ./randnums {case['size']} {case['seed']} | ./msa",
        rf"\s*Max:\s*{case['output']:d}\s*",
        comparer=match_re,
        name=f"T{num} {case['size']:,} Zahlen",
        description=f"Testfall {num} mit {case['size']:,} zufälligen Zahlen | Timeout {timeout}",
        points=1,
        timeout=timeout
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
