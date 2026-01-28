import string

def is_pangram(s):
    return set(s.lower()) >= set(string.ascii_lowercase) # same as issuperset https://docs.python.org/3/library/stdtypes.html#set

def is_pangram(s):
    return set(string.ascii_lowercase).issubset(s.lower())

def is_pangram(st):
    alpha = 'abcdefghijklmnopqrstuvwxyz'
    chs = {}
    for ch in st:
        chs[ch.lower()] = 1
    return all(ch in chs for ch in alpha)
