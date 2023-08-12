
def print_primes(n: int) -> None:
    noPrimes = [False] * (n+1)
    
    for prime in range(2, int(n**(0.5)) + 1):
        if noPrimes[prime]:
            continue
        for p in range(prime*prime, n+1, prime):
            noPrimes[p] = True
            
    print('\n'.join([str(p) for p in range(2, n+1) if not noPrimes[p]]))
    


if __name__ == '__main__':
    print_primes(int(input()))