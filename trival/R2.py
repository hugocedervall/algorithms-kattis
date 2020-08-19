



lenght = int(input())

sum = 0

for i in range(lenght):
    temp = str(input())

    sum += int(temp[0:-1])**int(temp[-1])

print(sum)