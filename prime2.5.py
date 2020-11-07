max = int(input('Range? '))
prime = [2, 3]
z = 0
for i in range(6, max, 6):
    x = [True, True]
    for j in prime:
        if x[0]: x[0] = (i-1) % j
        if x[1]: x[1] = (i+1) % j
        z = z + 1
        if not (x[0] or x[1]): break
    if x[0]: prime.append(i-1)
    if x[1]: prime.append(i+1)
print(prime)
print('Number of iterations: {}'.format(z))
print('Number of primes: {}'.format(len(prime)))
