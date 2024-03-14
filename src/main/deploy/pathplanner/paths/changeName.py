import os

for f in os.listdir("."):
  if "Sub" in f:
    os.remove(f)
