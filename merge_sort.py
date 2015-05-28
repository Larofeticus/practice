import random

p = [random.randint(1, 10000) for x in range(1, 10)]

print(p)

def merge(perm):
    #base case
    if len(perm) == 1 or len(perm) == 0:
        return perm[:]


    mid = int(len(perm)/2)
    L = perm[:mid]
    R = perm[mid:]
   
    L = merge(L)
    R = merge(R)

    lc = 0
    rc = 0
    out = []

    while lc < len(L) and rc < len(R):
        if L[lc] > R[rc]:
            out.append(R[rc])
            rc += 1
        else:
            out.append(L[lc])
            lc += 1

    #if either list gets exhausted just fill with rest of the other one
    while lc < len(L):
        out.append(L[lc])
        lc += 1

    while rc < len(R):
        out.append(R[rc])
        rc += 1

    return out

p = merge(p)

print(p)
