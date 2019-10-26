#!/usr/bin/python3

MOD = 0x7fffffff
X, XINV = 123456, 1473977140
#X, XINV = 1, 1

def fullhash(s):
    h = 0
    for c in s:
        h = (h*X+ord(c))%MOD
    return h

def positivehit(th, s, i, words, hashes):

    if th not in hashes: return False

    substr = s[:i] + s[i+1:]
    for j in hashes[th]:
        if substr == words[j]:
            return True
    return False

assert((X*XINV)%MOD == 1)

n = int(input())
words = [input() for _ in range(n)]
hashes = {}

for i in range(n):
    h = fullhash(words[i])
    if h not in hashes:
        hashes[h] = []
    hashes[h].append(i)

typo = False
for s in words:
    thistypo = False
    h, partial, XP = fullhash(s), 0, 1

    for i in range(len(s)-1, -1, -1):
        nextpartial = (partial+ord(s[i])*XP)%MOD
        th = (h-nextpartial)%MOD
        th = (th*XINV+partial)%MOD

        if positivehit(th, s, i, words, hashes):
            print(s)
            typo = True
            break

        partial = nextpartial
        XP = (XP*X)%MOD

if not typo:
    print("NO TYPOS")
