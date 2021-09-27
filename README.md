# CS50X-Speller-in-C-and-Python
A program (speller.c/.py, dictionary.c/.py) that takes two inputs, a dictionary .txt file and a text .txt file and spell checks every word in text.txt. The program first loads the dictionary in a hashtable by creating memory for each character of the word, parsing through each line of the dictionary and stripping white space. Next, for every word in text, it will run a hash function on it, returning some number that corresponds to that word. Afterwards, it will check if the word in text.txt is spelled correctly by referencing the hash number of each dictionary word. Afterwards, in the C variation, I will have to make sure I free any memory that I have used. At the end, it will output the total number of words in the dictionary, words misspelled, words in the text. As distribution code there is also an option to see how long it took for each section of the program to run. I will be benchmarking the total run time of each component of the program to see if a certain hash function (.c) performed faster than another function. Included is a Python version of the same program (dictionary.py).
