#!/usr/bin/python

import time

start = time.time()

def fib_r(x) :
    if (x <= 2):
        return 1
    return fib_r(x-1) + fib_r(x-2)


def fib_i(x) :
    a = 1
    b = 1
    fib = 1
    i = 2
    while i < x:
        fib = a +b
        a = b
        b = fib
        i+=1
        
    return fib

x = 1


#print ("Fib of " + str(x) + " = " + str(fib_r(x)))
print ("Fib of " + str(x) + " = " + str(fib_i(x)))

end = time.time()
print(end - start)


