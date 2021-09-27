"""
speller.py
Implements a spell-checker.
"""
import time
from sys import argv, exit
import re

from dictionary import check, load, size, unload

LENGTH = 45

#DICTIONARY = "dictionaries/large"

#check for correct number of args
if len(argv) != 2 and len(argv) != 3:
    exit("Usage: speller [dictionary] text")

#load data structure for timing
time_load, time_check, time_size, time_unload = 0.0, 0.0, 0.0, 0.0

#determine dictionary to use
dictionary = argv[1] if len(argv) == 3 else DICTIONARY

#load dictionary
before = time.process_time()
loaded = load(dictionary)
after = time.process_time()

#abort if dictionary not loaded
if not loaded:
    exit(f"Could not load {dictionary}.")

#calculate time to load dictionary
time_load = after - before

text = argv[2] if len(argv) == 3 else argv[1]
file = open(text, "r")
if not file:
    exit(f"Could not open {text}.")
    unload()
    exit(1)

#Prepare to report misspellings
print("\nMISSPELLED WORDS\n")

#prepare to spell-check
index, misspellings, words = 0, 0, 0
word = ""

#read in characters from text
while True:
    c = file.read(1)
    if not c:
        break
    #read in one character at a time including apostrophes
    if re.match(r"[A-Za-z]", c) or (c == "'" and index > 0):
        #append character to word
        word += c
        index += 1

        #if index is longer than MAX of 45 then add the last character and break.
        if index > LENGTH:

            while True:
                c = file.read(1)
                if not c or not re.match(r"[A-Za-z]", c):
                    break

            index, word = 0, ""

    #if character c is a digit and not an alphabet then break and reset the index
    elif c.isdigit():
        while True:
            c = file.read(1)
            if not c or (not c.isalpha() and not c.isdigit()):
                break
            index, word = 0, ""
        # if found word
    elif index > 0:
        words += 1
        #benchmark check appending the value after each check, and print misspelled words
        before = time.process_time()
        misspelled = not check(word)
        after = time.process_time()
        time_check += after - before
        if misspelled:
            print(word)
            misspellings += 1

        index, word = 0, ""
file.close()

#Benchmark time it takes to calculate size()
before = time.process_time()
n = size()
after = time.process_time()

time_size = after - before

#Benchmark unload()
before = time.process_time()
unloaded = unload()
after = time.process_time()

#Abort if dictionary not unloaded
if not unloaded:
    print(f"Could not load {dictionary}.")
    sys.exit(1)

time_unload = after - before

#Report Benchmarks
print(f"\nWORDS MISSPELLED:         {misspellings}")
print(f"WORDS IN DICTIONARY:    {n}")
print(f"WORDS IN TEXT:          {words}")
print(f"TIME IN load:           {time_load:.2f}")
print(f"TIME IN check:          {time_check:.2f}")
print(f"TIME IN size:           {time_size:.2f}")
print(f"TIME IN unload:         {time_unload:.2f}")
print(f"TOTAL TIME:             {time_load + time_check:.2f}")

#When successful
exit(0)