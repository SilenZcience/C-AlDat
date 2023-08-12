from testers.outputtests import *

tests = TestSuite("Aufgabe: Union-Find")
tests.add(StatusTest(
        "make",
        name="Kompilieren und Linken?",
        description="Funktioniert 'make'?",
        points = 0,
        critical=True
))

tests.add(RuntimeErrorTest(
    r"./unionfind < testcases/test6.in > /dev/null",
    name="Keine Runtime Error",
    description="Programm wirft keine Runtime Error mit -fsanitize?"
))

tests.add(CompareWithFileTest(
    r"./unionfind < testcases/test1.in",
    "testcases/test1.out",
    name="Funktioniert find?",
    description="Funktioniert find ohne union?"
))


tests.add(CompareWithFileTest(
    r"./unionfind < testcases/test2.in",
    "testcases/test2.out",
    name="benachbarte Union?",
    description="Union von benachbarten Menge / Größe 1?"
))


tests.add(CompareWithFileTest(
    r"./unionfind < testcases/test3.in",
    "testcases/test3.out",
    name="benachbarte Union (vertauscht)?",
    description="Union von benachbarten Menge / Größe 1 (vertauschte Operanden)?"
))

tests.add(CompareWithFileTest(
    r"./unionfind < testcases/test4.in",
    "testcases/test4.out",
    name="Vereinigung nach Größe?",
    description="Wird nach Größe vereinigt?"
))

tests.add(CompareWithFileTest(
    r"./unionfind < testcases/test5.in",
    "testcases/test5.out",
    name="Vereinigung nach Größe (vertauscht)?",
    description="Wird nach Größe vereinigt (vertauschte Operanden)?"
))

tests.add(CompareWithFileTest(
    r"./unionfind < testcases/test6.in",
    "testcases/test6.out",
    name="Union allgemmein?",
    description="allgemeine Fälle für union?",
    points=2
))

tests.add(CompareWithFileTest(
    r"./unionfind < testcases/test7.in",
    "testcases/test7.out",
    name="Union gleicher Mengen?",
    description="Union(x,y) mit x=y tut nichts?"
))


tests.add(CompareWithFileTest(
    r"./unionfind < testcases/test8.in",
    "testcases/test8.out",
    name="Union gleicher Mengen II?",
    description="Union(x,y) mit x=y tut nichts, Teil II?"
))






success = tests.run()
if not success:
    exit(1)
else:
    exit(0)

