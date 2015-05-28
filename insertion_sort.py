import random

p = [random.randint(1, 10000) for x in range(1,10)]

print(p)

for j in range(1, len(p)):
    item = p[j]
    i = j - 1
    while i >= 0 and p[i] > item:
        p[i+1] = p[i]
        i = i - 1
    p[i+1] = item

print(p)
