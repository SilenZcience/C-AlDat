import io

# In welcher Zeile wird welches Target ausgegeben?
def extract_order(make_output, targets):
  lines = io.StringIO(make_output)
  order = dict()
  for idx, line in enumerate(lines):
    for target in targets:
      if target.text in line:
        # kommt target mehrfach in Ausgabe vor?
        if target.name in order:
          order[target.name] = -1
          print(f"Ziel {target.name} kommt mehrfach vor (Zeilen {idx} und {order[target.name]})")

        else:
          order[target.name] = idx

  return order
