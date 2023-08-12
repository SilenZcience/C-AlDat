class Target:
  def __init__(self, name, depends=[], text="", points=1):
    self.name = name
    self.depends = depends
    self.text = text
    self.points = points

  def __str__(self):
    return self.name

def flatten_targets(target, flattened):
  if not target in flattened:
    flattened.append(target)

  for dependency in target.depends:
    flatten_targets(dependency, flattened)
