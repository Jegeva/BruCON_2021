#! /usr/bin/python3
import math

stepnum=1024
resolutionbits=10

def print_c_array(ar,name,sz):
    print("%s[%d]={" % (name,sz));
    for i in range(sz):
        print("%d," % (ar[i]),end='')
    print("};\n");
        

r=[abs(int((2**resolutionbits)*(math.sin(              i*(math.pi/stepnum))))) for i in range(stepnum)]
g=[abs(int((2**resolutionbits)*(math.sin((math.pi/2)  +i*(math.pi/stepnum))))) for i in range(stepnum)]
b=[abs(int((2**resolutionbits)*(math.sin((math.pi/4)    +i*(math.pi/stepnum))))) for i in range(stepnum)]

print_c_array(r,"wheel_r",stepnum)
print_c_array(g,"wheel_g",stepnum)
print_c_array(b,"wheel_b",stepnum)
