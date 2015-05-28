import random

p = [random.randint(1, 1000) for x in range(1,20)]

def partition(A, first, last):
    pivot = A[last]
    back = first
    for n in range(first, last):
        if A[n] < pivot:
            A[n], A[back] = A[back], A[n]
            back += 1
    A[last], A[back] = A[back], A[last]
    return back

def quicksort(A, first, last):
    if first < last:
        split = partition(A, first, last)
        quicksort(A, first, split-1)
        quicksort(A, split, last)

print(p)

quicksort(p, 0, len(p)-1)

print(p)
