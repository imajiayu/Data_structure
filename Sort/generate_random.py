import random
import os

dict={'10':"10",'100':"100",'1000':"1K",'10000':"10K",'100000':"100K",'1000000':"1M"}

def data_create(size):

    filepath="./"+dict[str(size)]+".txt"

    file = open(filepath, 'w')

    for i in range(size):
        file.write(str(random.randint(0, 2147483646) + 1) + " ")

    file.close()

for size in dict:
    data_create(int(size))

  

