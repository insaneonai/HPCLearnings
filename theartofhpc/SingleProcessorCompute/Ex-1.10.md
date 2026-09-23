### Question

Show that with a prime number of banks, any stride up to that number will be conflict free. Why do you think this solution is not adopted in actual memory architectures?

### Answer

A memory banked system divides memory into multiple independent banks so that multiple accesses can be serviced simultaneously. A common mapping is:

```
Bank = Address mod NumberOfBanks
```

For example, with 3 banks:
```
Address 0 -> Bank 0
Address 1 -> Bank 1
Address 2 -> Bank 2
Address 3 -> Bank 0
Address 4 -> Bank 1
Address 5 -> Bank 2
```

Consider stride = 1, 2

for stride = 1
```
0 -> Bank 0
1 -> Bank 1
2 -> Bank 2
```

for stride = 2
```
0 -> Bank 0
2 -> Bank 2
4 -> Bank 1
```

This tells us that If the number of banks is prime, every stride 1 ≤ s < p visits all banks before repeating.

#### Why not use a prime number of banks in real systems?

Power-of-two banks are cheap to compute, if we have prime number of banks computing ```stride mod prime``` is expensive requiring complex hardwares.