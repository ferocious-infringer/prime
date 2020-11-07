import math
max = int(input('Range? '))
prime = [2, 3]
z = 0
for i in range(6, max, 6):
    r = math.sqrt(i+1)
    x = [True, True]
    for j in prime:
        if x[0]: x[0] = (i-1) % j
        if x[1]: x[1] = (i+1) % j
        z = z + 1
        if not (x[0] or x[1]): break
        if j > r: break
    if x[0]: prime.append(i-1)
    if x[1]: prime.append(i+1)
print(prime)
print('Upper range: {}'.format(max))
print('Number of iterations: {}'.format(z))
print('Number of primes: {}'.format(len(prime)))
