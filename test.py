import re
from sys import argv
text = argv[1]
file = open(text, "r")

c = file.read(1)
while True:
    if not re.match(r"[A-Za-z]", c):
        print (c)
    else:
        exit("exit code 2")
        
#not c or not