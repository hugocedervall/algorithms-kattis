size = input().split()

row = int(size[0])
column = int(size[1])

map = []
for i in range(row):
    map.append(input())

def findWithSquash(x):
    amount = 0
    for i in range(row):
        for j in range(column):
            current_amount = 0
            current = ""

            if (i < row-1 and j < column-1):
                current += map[i][j] + map[i+1][j] + map[i][j+1] + map[i+1][j+1]

            if not ("#" in current):
                for k in range(len(current)):
                    if(current[k] == "X"):
                        current_amount += 1
            else:
                current = ""

            if(current_amount == x and not current == ""):
                amount += 1

    return amount


for i in range(5):
    print(findWithSquash(i))





