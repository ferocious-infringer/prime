max = int(input('Range? '))
prime = []
z = 0
for i in range(2, max):
    for x in prime:
	z = z + 1
        if not i % x: break
    else:
        prime.append(i)
print(prime)
print('Number of iterations: {}'.format(z))
print('Number of primes: {}'.format(len(prime)))
