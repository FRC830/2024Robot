import os

for f in os.listdir("."):
  if not (f.startswith("RED")):
    os.rename(f, "BLUE_"+f[0:])

