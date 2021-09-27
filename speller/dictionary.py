words = set()

def check(word):
    return word.lower() in words
def load(dictionary):
    #Open dictionary and give file handle.
    #Parse dictionary file and store individual words in data structure
    with open(dictionary, "r") as file:
        for line in file:
            words.add(line.rstrip("\n"))
            pass
    return True

def size():
    return len(words)
    
def unload():
    return True
