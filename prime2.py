max = int(input('Range? '))
prime = [2, 3]
z = 0
for i in range(6, max, 6):
    for j in prime:
	z = z + 1
        if not (i-1) % j: break
    else:
        prime.append(i-1)
    for j in prime:
	z = z + 1
        if not (i+1) % j: break
    else:
        prime.append(i+1)
print(prime)
print('Number of iterations: {}'.format(z))
print('Number of primes: {}'.format(len(prime)))
