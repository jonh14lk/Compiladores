import os

id = 1

with open('tokens.txt') as f:
    lines = f.readlines()
    for l in lines:
        ll = l.strip().split(" -> ")
        print(f"{id}      {ll[1]}      \'{ll[0]}\'")
        id += 1

print()
