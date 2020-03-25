import math
import time
import pandas as pd
import numpy as np
from collections import deque
import tkinter

def pierwsze_imperatywna(n):
    res = []
    for i in range(2, n):
        rge = math.floor(math.sqrt(i))
        if i == 2 or i == 3:
            res.append(i)
        else:
            for j in range(2, rge+1):
                if i%j == 0:
                    break
                elif j == rge:
                    res.append(i)
    return res


def pierwsze_skladana(n):
    return [x for x in range(2, n) if x == 2 or x == 3 or all(x % y != 0 for y in range(2, math.floor(math.sqrt(n))+1))]

def is_prime_fun(n):
    return len(list(filter(lambda k: n%k == 0 and n != 2, range(2,math.floor(math.sqrt(n))+1)))) == 0

def pierwsze_funkcyjna(n):
    return list(filter(is_prime_fun,range(2,n)))

def pierwsze_gen(n):
    def gen(n):
        Div = {}
        p = 2

        while p <= n:
            if p not in Div:
                yield p
                Div[p * p] = [p]
            else:
                for d in Div[p]:
                    Div.setdefault(d + p, []).append(d)
                del Div[p]
            p += 1

    return [p for p in gen(n)]


def timer(n, f):
    '''
    Args:
        f - funkcja.
            0 - imperatywna,
            1 - funkcyjna,
            2 - skladana
            3 - generator

    '''
    func = [pierwsze_imperatywna, pierwsze_funkcyjna, pierwsze_skladana, pierwsze_gen]
    t = time.time()
    func[f](n)

    return time.time() - t





features = ['n', 'imperatywna', 'funkcyjna', 'skladana', 'generator']
data = {}

for i in range(1, 6):
    n = 10 ** i
    data.setdefault('n', []).append(n)
    data.setdefault('imperatywna', []).append(timer(n, 0))
    data.setdefault('funkcyjna', []).append(timer(n, 1))
    data.setdefault('skladana', []).append(timer(n, 2))
    data.setdefault('generator', []).append(timer(n, 3))

results = pd.DataFrame(data)


results

'''
N = 100000
print(f"Czas dla wersji imperatywnej ", end = "")
t = time.time()
pierwsze_imperatywna(N)
t2 = time.time() - t
print(t2)

print(f"Czas dla wersji list składanych ", end = "")
t = time.time()
pierwsze_skladana(N)
t2 = time.time() - t
print(t2)

print(f"Czas dla wersji funkcyjnej ", end = "")
t = time.time()
pierwsze_funkcyjna(N)
t2 = time.time() - t
print(t2)
'''




Div = {}
Div[4] = [2]
Div[9] = [3]

for d in Div[4]:
    Div.setdefault(d + 4, []).append(d)
    print(d)

print(Div)

